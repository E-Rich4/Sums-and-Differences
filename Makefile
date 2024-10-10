#EXECUTION OF THE FRENCH ROYALTY
submission: evan_rich_c.o input.txt output.txt
	g++ evan_rich_c.o -o submission

#MAKE DA O's BY TYLER, THE CREATER
evan_rich_c.o: evan_rich_c.c
	g++ -c evan_rich_c.c

#FALL CLEANING
clean:
	rm -f *.o submission