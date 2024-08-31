def main():
	num = int(input())
	# Guess is in [gmin, gmax]
	# Note that it does include gmin or gmax
	gmin,gmax=1,10
	while num != 0:
		response = input()
		if response == "right on":
			if gmin <= num <= gmax:
				print("Stan may be honest")
			else:
				print("Stan is dishonest")
			gmin,gmax=1,10
		elif response == "too low":
			gmin = max(gmin, num+1)
		elif response == "too high":
			gmax = min(gmax, num-1)
		num=int(input())
main()