from random import randint
with open("/home/czarnobylu/.files/milijon.csv",'w') as f:
	f.write("DATA1,DATA2,DATA3,DATA4\n")
	for i in range(1000000):
		a = ""
		for i in range(4):
			a+=(str(randint(0,100))+',')
		f.write(a[:-1]+'\n')
