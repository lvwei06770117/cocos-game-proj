::简化cocos2dx项目创建
::by zhangzaiyaun suqixu@126.com
::2014-05-18 10:00:37

color 0a

@echo off
echo =============新建项目==============
set /p project_name=请输入项目的名称：
set /p project_package=请输入项目包名称：

set project_path=%~dp0

set cocos2dx_path=F:\tools\cocos2d-x-3.0rc2\
set new_project=%cocos2dx_path%tools\cocos2d-console\bin\cocos.py new %project_name% -p %project_package% -l cpp -d %project_path%
set android_src_path=%cocos2dx_path%cocos\2d\platform\android\java\src\org\cocos2dx\
set android_des_path=%project_path%\%project_name%\proj.android\src\org\cocos2dx\
set open_win32_sln=%project_path%\%project_name%\proj.win32\%project_name%.sln

echo 名  称：%project_name%
echo 包  名：%project_package%
echo 路  径：%project_path%
echo 库目录：%cocos2dx_path%

echo 正在创建新项目...
%new_project%

echo 正在复制android库文件...
xcopy %android_src_path%. %android_des_path% /s/e

echo 创建完成正在打开vs...
%open_win32_sln%