import os
path=input('请输入文件路径(结尾加上/)：')

#获取该目录下所有文件，存入列表中
fileList=os.listdir(path)

n=10000
for i in fileList:
    
    #设置旧文件名（就是路径+文件名）
    oldname=path+ os.sep + "p_"+str(n-10000+1)+".0.bin"
    
    #设置新文件名
    newname=path + os.sep +'a'+str(n+1)+'.bin'
    
    os.rename(oldname,newname)   #用os模块中的rename方法对文件改名
    print(oldname,'======>',newname)
    
    n+=1