compile:
	@g++ -o ./build/spotify ./code/*.cpp

run: compile
	@./build/spotify