import os,sys,struct

def main():
    if not os.path.exists("data.bin") or not os.path.exists("list.bin"):
        print("File not exist")
        return
    filedata = open("data.bin", 'rb')
    filelist = open("list.bin", 'rb')
    datadata = b'' + filedata.read()
    datalist = b'' + filelist.read()
    pl = 0
    os.system("mkdir data")
    listsize = os.path.getsize("list.bin")
    while pl < listsize:
        filelength,drop,filestart = struct.unpack("<3I",datalist[pl:pl+12])
        readdata = datadata[filestart:filestart+filelength]
        filename = cstr(datalist[pl+16:pl+32])
        wrfile = open("data/"+filename, 'wb')
        wrfile.write(readdata)
        wrfile.close()
        pl += 80
    print("Complete!")

def cstr(s):
    p = "{}s".format(len(s))
    s = struct.unpack(p,s)[0]
    return str(s.replace(b"\x00",b""),encoding = "sjis")
    
if __name__ =="__main__":
    main()
    
