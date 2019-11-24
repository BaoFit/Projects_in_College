
from django import forms

class MyUserCreationForm(forms.Form):
    name = forms.CharField(label="用户名", max_length=128,widget=forms.TextInput(attrs={'class': 'txt tabInput', 'placeholder': '用户名'}))
    password1 = forms.CharField(label="密码1", max_length=256,
                                widget=forms.PasswordInput(attrs={'class': 'txt tabInput', 'placeholder': '密码,4-16位数字/字母/特殊符号(空格除外)'}))