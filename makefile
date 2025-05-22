git :
	git add .
	git commit -m "added override" 
	git push

run :
	g++ -std=c++17 -g *.cpp -o a
	./a