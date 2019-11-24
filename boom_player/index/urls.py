#coding=utf-8
from django.conf.urls import url
from . import views

# 设置首页的URL地址信息
urlpatterns = [
    url('song_id_(\d+)', views.indexView, name='index'),
    url('^profile.html',views.profileView,name='profile'),
    url('^logout.html',views.logoutView,name='logout'),
    url('^mylove.html',views.myloveView,name='mylove'),
    url('^cf.html',views.cfView,name='cf'),
    url('^hotmusic.html',views.hotmusicView,name='hotmusic'),
    url('^mycollected.html',views.mycollectedView,name='mycollected'),
    url('^search.html',views.searchView,name='search'),
]
