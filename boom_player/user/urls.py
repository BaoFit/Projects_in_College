#coding=utf-8
from django.conf.urls import url
from . import views
urlpatterns=[
    url('^login.html',views.loginView,name='login'),
]