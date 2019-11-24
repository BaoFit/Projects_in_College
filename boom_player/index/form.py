
from django import forms

class MyprofileForm(forms.Form):
    pass1 = forms.CharField(label="新密码1", max_length=256,widget=forms.PasswordInput(attrs={'class': 'txt tabInput', 'placeholder': '新密码'}))
    pass2 = forms.CharField(label="新密码2", max_length=256, widget=forms.PasswordInput(attrs={'class': 'txt tabInput', 'placeholder': '确认密码'}))
    oldpass = forms.CharField(label="原密码", max_length=256, widget=forms.PasswordInput(attrs={'class': 'txt tabInput', 'placeholder': '原密码'}))

class MysearchForm(forms.Form):
    tab = forms.CharField(label="content", max_length=256, widget=forms.TextInput(attrs={'class': 'txt tabInput', 'placeholder': '歌名/歌手','size':60}))