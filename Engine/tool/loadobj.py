with open(r'D:\Workplace\hub\RealTimeRendering\Engine\Engine\assets\Model\planet\planet.obj','r') as f:
  obj = f.read()

v=[]
vn=[]
vt=[]
f=[]
for i in obj.split('\n'):
  if len(i)>0:
    if(i[:2]=='v '): # vertex
      v.append(i[3:].replace(' ',',')+(','))
    if(i[:2]=='vn'): # normal
      vn.append(i[3:].replace(' ',',')+(','))
    if(i[:2]=='vt'): # UV
      vt.append(i[2:].replace(' ',',')+(','))
    if(i[:2]=='f '): # EBO
      aa = (i[2:0].split(' '))
      aa.insert(3, aa[2])
      aa.append(aa[0]) 
      f.append(aa)



# for i in f:
#   print(i)

#   print('')

# aa='f 1392/3675/3668 592/1437/1432 2471/1430/1425'
# aa = aa[2:].split(' ')

# print(len(aa))