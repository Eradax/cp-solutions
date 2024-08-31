k,b=map(input().count,'kb')
print('none'*(b+k<1)or'bkoi'[b<k::2]+'kbia'[k<b::2])
