#!/usr/bin/env python
# coding: utf-8

# In[36]:


import matplotlib.pyplot as plt
import numpy as np


# In[37]:


file=open("output.txt","r")
suceptable=[]
infected=[]
recoverd=[]
time=[]


# In[38]:


for i in range (0,31):
    t=file.readline()
    x=t.split()
    x=np.array(x,dtype=float)
    time.append(x[0])
    infected.append(x[1])
    suceptable.append(x[2])
    recoverd.append(x[3])


# In[39]:


#print(time)
#print(suceptable)
#print(infected)
#print(recoverd)


# In[40]:


plt.plot(time,infected)

plt.plot(time,suceptable)

plt.plot(time,recoverd)
plt.show()

# In[41]:





