import re
import codecs
from xml.etree.ElementTree import ParseError
from xml.etree import ElementTree as ET
import sys

STOPWORDS = ['the', 'a', 'as', 'be', 'but', 'by', 'an', 'and', 'or', 'is', 'are', 'we', 'us', 'of', 'at', 'for', 'in', 'with', 'on', 'to'] 

tuple_file=open('tuple.txt', 'w')
url_file = open('urls.txt', 'w')

def removes_stop_words(words):	
	non_stop_words_list = []
	for word in words:
		if word.lower() not in STOPWORDS:
			non_stop_words_list.append(word)
	return non_stop_words_list

def split_word(text):
	text = re.sub(ur"\W", " ", text)	
	words = text.split()
	words = removes_stop_words(words)
	return words

def main():
	if len(sys.argv) < 2:
		print "Usage: python 1_parse_file.py Filename"
		print "Filename: Wikipedia XML file to parse"
		sys.exit()
	filename = sys.argv[1]
	events = ['start', 'end', 'start-ns', 'end-ns']
	parser = ET.iterparse(filename)


	for event, element in parser:
		try:
			if element.tag == '{http://www.mediawiki.org/xml/export-0.8/}page':
				doc_id = element.find('{http://www.mediawiki.org/xml/export-0.8/}id')
				title = element.find('.//{http://www.mediawiki.org/xml/export-0.8/}title')
				text_tag = element.find('.//{http://www.mediawiki.org/xml/export-0.8/}text')

				if text_tag.text is not None:
					url = 'http://en.wikipedia.org/wiki/' + re.sub(" ", "_", title.text).encode('utf-8')
					url_file.write(doc_id.text + " " + url + "\n")

					total_text = text_tag.text + " " + title.text
					words = split_word(total_text)

					for word in words:
						tuple_file.write(word.lower().encode('utf-8') + " " + doc_id.text + '\n')		
				element.clear()	
		except:
			print "caught exception at "
			print element
			print title.text
			print doc_id.text	
	
	tuple_file.close()
	url_file.close()

	
if __name__ == "__main__":
	main()	







	
