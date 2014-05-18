index = {}

def addToIndex(pair):
	key = pair[0]
	value = pair[1]
	if key in index:
		index[key].add(value)
	else:
		index[key] = set()
		index[key].add(value)


def main():

	file_handle = open('index.txt', 'w')
	with open('tuple.txt') as infile:
		for line in infile:
			pair = line.split()
			addToIndex(pair)

	
	for key in index:
    		file_handle.write(key + " ")
    		for value in index[key]:
			file_handle.write(value + " ");
		file_handle.write('\n')
			
if __name__ == "__main__":
	main()

