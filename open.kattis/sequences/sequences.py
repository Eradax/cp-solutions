# Our modulus
mod = 10**9+7

# Rolling ans
ans = 0

# Count of how many ones we have seen
numOfOnes = 0

# Count of how many questionmarks we have seen 
numOfQuestions = 0

inp = input()
for i in inp:
	if i == '?':
		ans += ans
		isQuestionmark = True
	else:
		tmp = 0
		isQuestionmark = False

	if i == '1':
		numOfOnes += 1

	else:
		ans += (numOfQuestions+2*numOfOnes) * pow(2, numOfQuestions-1, mod)

	ans = ans % mod

	numOfQuestions += isQuestionmark

print(ans)