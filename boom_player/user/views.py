#coding=utf-8
from django.shortcuts import render,redirect
from . import models
from .form import MyUserCreationForm


#用户注册 登录
def loginView(request):
    user=MyUserCreationForm()
    if request.method == 'POST':
        #用户登录
        user = MyUserCreationForm(request.POST)
        if user.is_valid():
            if request.POST.get('password2', ''):
                username = user.cleaned_data['name']
                password1 = user.cleaned_data['password1']
                password2 = request.POST.get('password2', '')
                if password1 != password2:  # 判断两次密码是否相同
                    tips = "两次输入的密码不同！"
                    return render(request, 'login.html', locals())
                else:
                    same_name_user = models.User.objects.filter(name=username)
                    if same_name_user:
                        tips = "用户已经存在，请重新选择用户名！"
                        return render(request, 'login.html', locals())
                    new_user = models.User.objects.create()
                    new_user.name = username
                    new_user.password = password1
                    new_user.save()
                    tips = "注册成功！"
                    return render(request, 'login.html', locals())
            else:
                username = user.cleaned_data['name']
                password = user.cleaned_data['password1']
                try:
                    same_user = models.User.objects.get(name=username)
                    if password == same_user.password:
                        request.session['is_login'] = True
                        request.session['user_id'] = same_user.id
                        request.session['user_name'] = same_user.name
                        #tips = "登录成功！"
                        return redirect('index/song_id_10')
                    else:
                        tips = "密码错误！"#same_user.password+"!"
                except:
                    tips = "用户不存在！"
                return render(request, 'login.html', locals())
    #user=MyUserCreationForm()
    return render(request,'login.html',locals())






