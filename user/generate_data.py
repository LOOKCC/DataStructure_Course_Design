import random
import numpy as np
'''
print('Begin generate data,please wait...')
name = range(100)
pre = './data/'
suf = '.set'
def generate_friends():
    total = range(1,10000)
    finall = random.sample(total,2000)
    array = np.zeros((100,100))
    for i in finall:
        x = i//100
        y = i%100
        array[x][y] = 1
        array[y][x] = 1
    number = np.sum(array,axis=1)
    for i in range(100):
        file_name = str(i)+'_friends'
        f = open(pre+file_name+suf,'w')
        count = 0
        if(array[i][i] == 1):
            count = number[i]-1
        else:
            count = number[i]
        f.write(str(i)+' '+file_name+' '+str(int(count)))
        for k in range(100):
            if array[i][k] == 1 and i != k:
                f.write(' '+str(k))


def generate_fansfollows():
    total = range(1,10000)
    finall = random.sample(total,2000)
    fans = []
    follows = []
    for i in range(100):
        fans.append([])
        follows.append([])
    for i in finall:
        x = i//100
        y = i%100
        if x != y:
            fans[x].append(y)
            follows[y].append(x)
    for i in range(100):
        file_name_fans = str(i)+'_fans'
        fans_file = open(pre+file_name_fans+suf,'w')
        fans_file.write(str(i)+' '+file_name_fans+' '+ str(len(fans[i])))
        for j in fans[i]:
            fans_file.write(' '+str(j))
        
        file_name_follows = str(i)+'_follows'
        follows_file = open(pre+file_name_follows+suf,'w')
        follows_file.write(str(i)+' '+file_name_follows+' '+ str(len(follows[i])))
        for j in follows[i]:
            follows_file.write(' '+str(j))

generate_friends()
generate_fansfollows()
'''
f = open('test.set','w')
s = 'second_friends '
for i in range(100):
    f.write(s + str(i) +'\n')
f.write('exit\n')




