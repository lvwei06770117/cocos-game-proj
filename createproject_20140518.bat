::��cocos2dx��Ŀ����
::by zhangzaiyaun suqixu@126.com
::2014-05-18 10:00:37

color 0a

@echo off
echo =============�½���Ŀ==============
set /p project_name=��������Ŀ�����ƣ�
set /p project_package=��������Ŀ�����ƣ�

set project_path=%~dp0

set cocos2dx_path=F:\tools\cocos2d-x-3.0rc2\
set new_project=%cocos2dx_path%tools\cocos2d-console\bin\cocos.py new %project_name% -p %project_package% -l cpp -d %project_path%
set android_src_path=%cocos2dx_path%cocos\2d\platform\android\java\src\org\cocos2dx\
set android_des_path=%project_path%\%project_name%\proj.android\src\org\cocos2dx\
set open_win32_sln=%project_path%\%project_name%\proj.win32\%project_name%.sln

echo ��  �ƣ�%project_name%
echo ��  ����%project_package%
echo ·  ����%project_path%
echo ��Ŀ¼��%cocos2dx_path%

echo ���ڴ�������Ŀ...
%new_project%

echo ���ڸ���android���ļ�...
xcopy %android_src_path%. %android_des_path% /s/e

echo ����������ڴ�vs...
%open_win32_sln%