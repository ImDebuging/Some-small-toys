def CRCcode(basedata,Gx):
    s = ''.join(map(str,Gx))
    gx = int(s,2)
    basedata.extend(['0']*(len(Gx)-1)) # 给原始数据末尾补0
    index = basedata.index('1')
    index = index + 1
    while len(basedata)-index >= len(Gx)-1:
        s = ''.join(basedata[index-1:index - 1 +len(Gx)])
        num = int(s,2)
        num = num ^ gx
        alt = [str(i) for i in bin(num)[2:]]
        while len(alt)<len(Gx):
            alt.insert(0,'0')
        basedata[index - 1:index - 1 + len(Gx) ] = alt
        index = basedata.index('1')
        index = index + 1
    return basedata

if __name__ =="__main__":
    print(''.join(CRCcode([c for c in "101001"],[c for c in "1101"])))
