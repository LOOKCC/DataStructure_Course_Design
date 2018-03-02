import random
print('Begin generate data,please wait...')
name = range(100)
action = ['fans','friends','follows']
pre = './data/'
suf = '.set'
total = range(1,1000)
for i in name:
    for j in range(3):
        number = random.randint(100,200)
        finall = random.sample(total,number)
        file_name = str(i)+'_'+action[j]
        f = open(pre+file_name+suf,'w')
        f.write(file_name+' '+str(number))
        for k in range(len(finall)):
            f.write(' '+str(finall[k]))
print('Generate OK')
