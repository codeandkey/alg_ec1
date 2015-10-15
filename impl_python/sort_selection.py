import time
import sys

INPUT_FILE="input.dat"

def sort(list):
	for i in range(0, len(list) - 1):
		max = list[i]
		max_index = i

		for j in range(i + 1, len(list)):
			if list[j] < max:
				max = list[j]
				max_index = j

		if max_index != i:
			tmp = list[max_index]
			list[max_index] = list[i]
			list[i] = tmp

def main():
	list = []

	with open(INPUT_FILE, "rb") as f:
		byte = f.read(4)
		while byte:
			list.append(int.from_bytes(byte, byteorder='little'))
			byte = f.read(4)

	print("Loaded file into " + str(len(list)) + " elements.")
	
	ref_time = time.clock()
	sort(list)
	total_time = time.clock() - ref_time;

	print("Time : " + '%f' % (total_time * 1000) + " milliseconds.")
	print("View results? (y/N) ")

	if sys.stdin.read(1) == 'y':
		for i in list:
			print(str(i) + " ")

if __name__ == "__main__":
	main()
