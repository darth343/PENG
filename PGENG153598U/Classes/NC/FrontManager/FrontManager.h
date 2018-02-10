#ifndef FRONTMANAGER_H_
#define FRONTMANAGER_H_

#define ADD_INIT_FUNCTION(CLASS,INSTANCE,FUNCTION)\
{\
	FrontManager::Getinstance()\
}\

class FrontManager
{
public:
	FrontManager() {}
	~FrontManager() {}

	static FrontManager& Getinstance()
	{
		static FrontManager Instance;
		return Instance;
	}
private:
	FrontManager(FrontManager const&);
	void operator=(FrontManager const&);
};

FrontManager::FrontManager()
{
}

FrontManager::~FrontManager()
{
}

#endif // !FRONTMANAGER_H_

