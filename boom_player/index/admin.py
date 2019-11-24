
from django.contrib import admin
from .models import *

admin.site.site_title="BOOM PLAYER 后台管理系统"
admin.site.site_header="BOOM PLAYER 后台管理"
admin.site.register(Song)
admin.site.register(Dynamic)