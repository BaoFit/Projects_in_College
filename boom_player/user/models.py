from django.db import models

# Create your models here.
'''用户信息表'''
class User(models.Model):
    name=models.CharField(max_length=128,unique=True)#用户账号名称
    password=models.CharField(max_length=256)#用户登录密码
    c_time=models.DateTimeField(auto_now_add=True)#自动保存时间

#输出实例对象时，调用这个方法
    def __str__(self):
        return self.name

    #定义User显示的名字
    class Meta:
        ordering = ['c_time']
        verbose_name='用户'
        #模型的复数形式
        verbose_name_plural='用户'