from random import randint
with open("/home/czarnobylu/.files/testing.csv",'w') as f:
	f.write("RISING,FALLING,RANDOM\n")
	range_size=1000000
	for i in range(range_size):
		a = ""
		a+=str(i)+","+str(range_size-i-1)+","+str(randint(0,1000))+","
		f.write(a[:-1]+'\n')
