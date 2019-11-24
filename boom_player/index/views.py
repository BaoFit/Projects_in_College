from django.shortcuts import render,redirect
from user.models import User
from . import form
from . import cf_item
from index.models import *
import io
from django.db.models import Q
from django.db import connection

# Create your views here.
def indexView(request,song_id):
    if request.session.get('is_login') is not True:
        return redirect('/user/login.html')
    userid=request.session.get('user_id')
    # 相关歌曲
    song_type = Song.objects.values('song_type').get(song_id=song_id)['song_type']
    song_relevant = Song.objects.filter(Q(song_type=song_type),~Q(song_id=song_id)).values('song_id','song_name','song_img').order_by('-song_release').all()[:7]
    is_loved = "😑😑😑"
    is_collected = "加入歌单"

    # 歌曲信息
    song_info = Song.objects.get(song_id=int(song_id))
    # 播放列表
    play_list = request.session.get('play_list', [])
    song_exist = False
    if play_list:
        for i in play_list:
            if int(song_id) == i['song_id']:
                song_exist = True
    if song_exist == False:
        play_list.append({'song_id': int(song_id), 'song_singer': song_info.song_singer,
                          'song_name': song_info.song_name, 'song_time': song_info.song_time})
    request.session['play_list'] = play_list

    # 歌词
    if song_info.song_lyrics != u'暂无歌词':
        f = io.open('static/songLyric/' + song_info.song_lyrics, 'r', encoding='utf-8')
        song_lyrics = f.read()
        f.close()
    print(song_info.song_lyrics)
    # 添加播放次数
    dynamic_info = Dynamic.objects.filter(song_id=int(song_id),user_id=userid).first()
    # 判断动态信息是否存在,在原来基础上加１
    if dynamic_info:
        dynamic_info.dynamic_plays += 1
        dynamic_info.save()
        if dynamic_info.is_loved == 1:
            is_loved="😊😊😊"
        elif dynamic_info.is_loved == -1:
            is_loved="☹☹☹"
        if dynamic_info.is_collected == 1:
            is_collected="移除歌单"
        else:
            is_collected="加入歌单"
        # 若动态信息不存在，则创建新的动态信息
    else:
        dynamic_info = Dynamic(dynamic_plays=1, dynamic_search=0,is_loved=0,is_collected=0,song_id=song_id,user_id=userid)
        dynamic_info.save()
    #判断动态信息中喜爱程度
    if 'lovebt' in request.POST:
        if dynamic_info.is_loved == 1:
            dynamic_info.is_loved=-1
            is_loved="☹☹☹"
        elif dynamic_info.is_loved==-1:
            dynamic_info.is_loved=0
            is_loved="😑😑😑"
        else:
            dynamic_info.is_loved=1
            is_loved = "😊😊😊"
        dynamic_info.save()
    if 'collectbt' in request.POST:
        if dynamic_info.is_collected == 1:
            dynamic_info.is_collected=0
            is_collected="加入歌单"
        else:
            dynamic_info.is_collected=1
            is_collected = "移除歌单"
        dynamic_info.save()
    return render(request,'index.html',locals())

def profileView(request):
    # 登录验证，只有登录之后才可以进入这个页面，否则返回登录页面
    if request.session.get('is_login') is not True:
        return redirect('/')
    profileform = form.MyprofileForm()
    if request.method == 'POST':
        # 修改密码
        profileform = form.MyprofileForm(request.POST)
        if profileform.is_valid():
            oldpassword=profileform.cleaned_data['oldpass']
            password1 = profileform.cleaned_data['pass1']
            password2 = profileform.cleaned_data['pass2']
            if password1!=password2:
                protips = "两次输入的密码不同！"
                return render(request, 'profile.html', locals())
            else:
                username=request.session.get('user_name')
                user=User.objects.filter(name=username,password=oldpassword).first()
                if user is not None:
                    user.password=password1
                    user.save()
                    protips = "密码修改成功"
                else:
                    protips = "密码错误！"
    return render(request,'profile.html',locals())

def logoutView(request):
    request.session['is_login']=False
    request.session.flush()
    return redirect('/')

#个性化推荐
def cfView(request):
    #登录验证，只有登录之后才可以进入这个页面，否则返回登录页面
    if request.session.get('is_login') is not True:
        return redirect('/')
    #基于项目的协同过滤推荐
    hottips = " 个 性 推 荐 "
    userid=request.session.get('user_id')
    cursor = connection.cursor()#获取游标
    #sql从用户动态表中查询用户对歌曲的评分，评分直接在sql查询语句中计算，输出结果
    cursor.execute("select distinct user_id as user,song_id as song,is_collected*2+is_loved*2+"
                   "(case when dynamic_plays < 2 then 0 "
                   "when dynamic_plays <5 then 1 when dynamic_plays<17 then 2 when dynamic_plays<65 then 3 else 4 end) as score from index_dynamic")
    #以列表套字典的数字形式返回查询结果
    data1 = dictfetchall(cursor)
    data={}
    #将输出结果变为字典套字典的二维矩阵形式
    for line in data1:
        data.setdefault(line['user'], {})
        data[line['user']][line['song']]=line['score']
    cursor.close()
    #计算推荐结果
    try:
        itemsAllsim = cf_item.calSimilarItems(data)
        result=cf_item.getrecommendations(data,userid,itemsAllsim)
        cfsong_info = []
        for (a,b) in result:
            s={}
            s['song_id']=b
            s['song_name']=Song.objects.values('song_name').get(song_id=b)['song_name']
            s['song_singer']=Song.objects.values('song_singer').get(song_id=b)['song_singer']
            s['song_time']=Song.objects.values('song_time').get(song_id=b)['song_time']
            cfsong_info.append(s)
    except:
        cursor = connection.cursor()
        cursor.execute(
            "select distinct a.song_id,a.song_name,a.song_singer,a.song_time,sum(b.dynamic_plays) as su "
            "from index_song as a,index_dynamic as b where a.song_id=b.song_id group by a.song_id,a.song_name,a.song_singer,a.song_time order by su desc limit 20")
        cfsong_info = dictfetchall(cursor)
        cursor.close()
        #推荐的歌曲数量不足20首时，添加最热门的歌曲
    #防冷启动策略
    if len(cfsong_info)<20:
        cursor = connection.cursor()
        cursor.execute(
            "select distinct a.song_id,a.song_name,a.song_singer,a.song_time from index_song as a,index_dynamic as b where a.song_id=b.song_id "
            "group by a.song_id,a.song_name,a.song_singer,a.song_time order by sum(b.dynamic_plays) desc limit 20")
        song_info = dictfetchall(cursor)
        i=len(cfsong_info)
        if i>0:
             for line in song_info:
                if line not in cfsong_info:
                     cfsong_info.append(line)
                     i=i+1
                     if i==20:break
        else:
            cfsong_info=song_info
        cursor.close()
        #推荐的歌曲超过20首时，减少推荐数量
    if len(cfsong_info)>20:
        cfsong_info=cfsong_info[:20]
    return render(request,'cf.html',locals())

def hotmusicView(request):
    if request.session.get('is_login') is not True:
        return redirect('/')
    cursor = connection.cursor()
    cursor.execute("select distinct a.song_id,a.song_name,a.song_singer,a.song_time,a.song_release from index_song as a order by a.song_release desc limit 20")
    hottips=" 新 增 歌 曲 "
    hotsong_info = dictfetchall(cursor)
    cursor.close()
    return render(request, 'hotmusic.html', locals())

def mycollectedView(request):
    if request.session.get('is_login') is not True:
        return redirect('/')
    userid=request.session.get('user_id')
    cursor = connection.cursor()
    cursor.execute("select distinct a.song_id,a.song_name,a.song_singer,a.song_time from index_song as a,index_dynamic as b where a.song_id=b.song_id and b.is_collected=1 and b.user_id='%d'"%userid)
    collecttips=""
    collectsong_info = dictfetchall(cursor)
    if collectsong_info is None:
        collecttips="您还没有将歌曲加入名单！"
    cursor.close()
    return render(request, 'mycollected.html', locals())

def myloveView(request):
    if request.session.get('is_login') is not True:
        return redirect('/')
    userid = request.session.get('user_id')
    cursor = connection.cursor()
    cursor.execute(
        "select distinct a.song_id,a.song_name,a.song_singer,a.song_time from index_song as a,index_dynamic as b where a.song_id=b.song_id and b.is_loved=1 and b.user_id='%d'" % userid)
    lovetips = ""
    lovesong_info = dictfetchall(cursor)
    if lovesong_info is None:
        lovetips = "您还没有喜爱的歌曲！"
    cursor.close()
    return render(request, 'mylove.html', locals())

def searchView(request):
    if request.session.get('is_login') is not True:
        return redirect('/')
    s=form.MysearchForm(request.POST)
    if s.is_valid():
        kword = s.cleaned_data['tab']

    song_info = Song.objects.values('song_id', 'song_name', 'song_singer', 'song_time').order_by(
        '-song_release').all()
    if 'subSerch' in request.POST:
        if kword:
            # Q是SQL语句里的or语法
            song_info = Song.objects.values('song_id', 'song_name', 'song_singer', 'song_time').filter(Q(song_name__icontains=kword) | Q(song_singer__icontains=kword)).order_by('-song_release').all()
    return render(request, 'search.html', locals())

def dictfetchall(cursor):
    columns = [col[0] for col in cursor.description]
    return [
        dict(zip(columns, row))
        for row in cursor.fetchall()
    ]

def dict_slice(ori_dict, start, end):
    """
    字典类切片
    :param ori_dict: 字典
    :param start: 起始
    :param end: 终点
    :return:
    """
    slice_dict = {k: ori_dict[k] for k in list(ori_dict.keys())[start:end]}
    return slice_dict