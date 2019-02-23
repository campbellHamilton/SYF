class Menu
{
public:
	Menu();
	void game();
	bool start();
private:
	int shootWait = 0;
	void wait();
	void wait(int);
	int movement = 2;//this controls what movement scheme where using
	//Toggles the bullet bouncing mutator
	bool bulletBounceToggle = false;
};

