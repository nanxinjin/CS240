
int
main(int argc, char ** argv) {
	int c;
	int line;
	printf("Program to count lines. Type a string and ctrl-d to exit\n");
	while ((c = getchar()) != -1){
		if(c == '\n'){
		line ++;
		}
	}
	printf("Total lines: %d\n",line);
	

}
