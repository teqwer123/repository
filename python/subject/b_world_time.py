
# 0 서울
# 1 뉴욕
# 2 베이징
# 3 런던
# 4 파리
# 5 로마
# 6 마드리드
# 7 취리히
time = [1600,300,1500,800,900,900,900,900]
name = ['서울','뉴욕','베이징','런던','파리','로마','마드리드','취리히']
want_time = 0
choice = 0

while 1:
    
    print('1. 서울 시간 입력 2. 세계 시간 수정 3. 종료')
    choice = int(input())
    # 시간 입력
    if choice == 1:
        print('서울 시간 입력:(13시라면 1300 형태로 입력)')
        want_time = int(input())
        
        if want_time > time[0]:
            want_time = want_time-time[0]

            for i in range(0,8):
                time[i]+=want_time
                if time[i] >=2400:
                    time[i]-=2400
                print(f'{name[i]} 시간 : {time[i]}')

        elif want_time < time[0]:
            want_time = time[0]-want_time
            for i in range(0,8):
                time[i]-=want_time
                if time[i] < 0:
                    time[i]=2400+time[i]
                print(f'{name[i]} 시간 : {time[i]}')
        else:
            want_time=0
            print('아무것도 실행 안함')
        
        
            


    
        
    # 세계 시간 수정
    elif choice == 2:
        print('어느 도시를 수정하시겠습니까?')
        print('1.서울 2. 뉴욕 3. 베이징 4. 런던 5. 파리 6. 로마 7. 마드리드 8. 취리히')
        choice = int(input())
        if choice == 1:
            # 서울
            print('서울 시간 수정:')
            want_time=int(input())   
            if time[0] >want_time:
                want_time = time[0]-want_time
                for i in range(0,8):
                    time[i]-=want_time
                    if time[i] < 0:
                        time[i] = 2400+time[i]
                    print(f'{name[i]} 시간 : {time[i]}')

            elif want_time > time[0]:
                want_time = want_time - time[0]
                for i in range(0,8):
                    time[i]+=want_time
                    if time[i] >=2400:
                        time[i]-=2400
                    print(f'{name[i]} 시간 : {time[i]}')

            else:
                print('아무것도 안함')
            



        elif choice == 2:
        elif choice == 3:
        elif choice == 4:
        elif choice == 5:
        elif choice == 6:
        elif choice == 7:
        elif choice == 8:
    
    elif choice == 3:
        break
    
    want_time = 0

    