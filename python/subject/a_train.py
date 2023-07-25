a = ['','',0,0]

def cal_time(st,tt):
    a[2] = int(st)
    a[3] = int(tt)

    hour = a[2]/100
    min = a[2]-(hour*100)
    if a[3] >= 100:
        t_hour = a[3]/100
        t_min = a[3]-(t_hour*100)
    elif a[3] < 100:
        t_hour = 0
        t_min = a[3]
    hour+=t_hour
    min+=t_min
    
    if min >= 60:
        hour+=1
        min-60
    if hour >= 2400:
        hour-2400
        
    return ((hour)*100)+min

print('출발지: ')
a[0] = input()
print('목적지: ')
a[1] = input()
print('출발시간:((ex)13시일시 -> 1300 라고 입력) ')
a[2] = input()
print('소요시간: ((ex)30분 소요 시 -> 30 이라고 입력, 1시간 30분 소요 시 -> 130이라고 입력)')
a[3] = input()

print('발권되었습니다')
print('출발지:',a[0])
print('목적지:',a[1])
print('출발시간:',a[2])
print('소요시간:',a[3])
print('도착시간:',cal_time(a[2],a[3]))



def update_info(choice):
    global a
    print('update_info 함수 실행')
    choice = int(choice)
    thousand = 0
    hundred = 0
    ten = 0
    one =0
    if choice >=1000:
        thousand = choice//1000
        hundred = (choice-(thousand*1000))//100
        ten = (choice-((thousand*1000)+(hundred*100)))//10
        one = (choice-((thousand*1000)+(hundred*100)+(ten*10)))
    elif choice >=100:
        hundred = choice//100
        ten = (choice-((thousand*1000)+(hundred*100)))//10
        one = (choice-((thousand*1000)+(hundred*100)+(ten*10)))
    elif choice >= 10:
        ten = choice//10
        one = (choice-((thousand*1000)+(hundred*100)+(ten*10)))
    elif choice >= 1:
        one = choice
    if thousand==1 or hundred==1 or ten==1 or one==1:
        print('출발지 수정:')
        a[0] = input()
    if thousand==2 or hundred==2 or ten==2 or one==2:
        print('목적지 수정:')
        a[1] = input()
    if thousand==3 or hundred==3 or ten==3 or one==3:
        print('출발시간 수정:')
        a[2] = input()
    if thousand==4 or hundred==4 or ten==4 or one==4:
        print('소요시간 수정:')
        a[3] = input()
    print('update_info 완료')
    
    



print('발권 정보를 수정하시겠습니까?(y/n)')
yesorno = input()
if yesorno == 'y':
    print('어떤 정보를 수정하시겠습니까?(수정하시고 싶은 항목이 만약 복수이고 그 항목의 번호가 1번과 4번이라고 할 때, 14라고 입력해주시기 바랍니다.)')
    print('1. 출발지 2. 목적지 3. 출발시간 4. 소요시간')
    choice = input()
    update_info(choice)
    print('수정되었습니다')
    print('출발지:',a[0])
    print('목적지:',a[1])
    print('출발시간:',a[2])
    print('소요시간:',a[3])
    print('도착시간:',cal_time(a[2],a[3]))

elif yesorno =='n':
    print('수정 취소')
