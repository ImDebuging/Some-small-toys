#中国象棋中，一匹马能走到什么位置？
startIndex = [2,1]  # 马起始的位置在（2，1）
possiblePos = [[2,1]]    # 起始位置也在可能的位置里
posDirection = [[2,1],[2,-1],[-2,1],[-2,-1],[1,2],[1,-2],[-1,2],[-1,-2]]   # 马跳一次坐标的变化

tempQue=[]

def CheckPos(pos):
    if pos[0] > 0 and pos[0] <= 9 and pos[1] > 0 and pos[1] <= 10:
        return True
    else:
        return False

def GetPosIndex(stepIndexQue):  # 获得马跳一步的所有坐标
    if len(stepIndexQue) == 0:  # 列表为空，说明已经无路可走
        return False
    for pos in stepIndexQue:
        for dir in posDirection:
            tempPos = pos
            tempPos = [x + y for x,y in zip(tempPos,dir)]
            if tempPos not in possiblePos and CheckPos(tempPos) == True:
                possiblePos.append(tempPos)
                tempQue.append(tempPos)
    return True
    # for dir in posDirection:
    #     tempPos = startIndex
    #     tempPos = [x + y for x,y in zip(tempPos,dir)]
    #     if tempPos not in possiblePos and CheckPos(tempPos) == True:
    #         possiblePos.append(tempPos)

def main():
    stepIndexQue = [[2, 1]]  # 马跳一次，所有可能的坐标，记录在这个队列里
    while(GetPosIndex(stepIndexQue) == True):
        lenOfQue = len(stepIndexQue)
        for i in tempQue:
            stepIndexQue.append(i)
        for i in range(0,lenOfQue):
            stepIndexQue.pop(0)
        tempQue.clear()

    sorted_possiblePos = sorted(possiblePos,key = lambda x: (x[1],x[0]))

    for i in sorted_possiblePos:
        print(i)

if __name__ == "__main__":
    main()