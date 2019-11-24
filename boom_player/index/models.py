from django.db import models
# Create your models here.
#歌曲信息表
class Song(models.Model):
    song_id=models.AutoField('序号',primary_key=True)
    song_name=models.CharField('歌名',max_length=50)
    song_singer=models.CharField('歌手',max_length=50)
    song_time=models.CharField('时长',max_length=10)
    song_album=models.CharField('专辑',max_length=50)
    song_languages=models.CharField('语种',max_length=20)
    song_type=models.CharField('类型',max_length=20)
    song_release=models.CharField('发行时间',max_length=20)
    song_img=models.CharField('歌曲图片',max_length=20)
    song_lyrics=models.CharField('歌词',max_length=50,default='暂无歌词')
    song_file=models.CharField('歌曲文件',max_length=50)

    def __str__(self):
        return str(self.song_name)
    class Meta:
        verbose_name='歌曲信息'
        verbose_name_plural='歌曲信息'
#用户动态信息表
class Dynamic(models.Model):
    dynamic_id=models.AutoField('序号',primary_key=True)
    user=models.ForeignKey('user.User',on_delete=models.CASCADE,verbose_name='用户名')#外键
    song=models.ForeignKey(Song,on_delete=models.CASCADE,verbose_name='序号')#外键
    dynamic_plays = models.IntegerField('播放次数')
    dynamic_search = models.IntegerField('搜索次数')
    is_loved = models.IntegerField('是否喜欢',default=0)
    is_collected=models.IntegerField('是否收藏',default=0)

    class Meta:
        verbose_name='歌曲动态'
        verbose_name_plural='歌曲动态'


