#include "APM_Practica13.h"
#include <vector>

int main()
{
	std::vector<CImage*> tImages;

	CPNG png;
	CPNG png1;
	CPNG png2;
	CPNG png3;
	
	CJPG jpg;
	CJPG jpg1;
	CJPG jpg2;
	CJPG jpg3;

	CRAW raw;
	CRAW raw1;
	CRAW raw2;
	CRAW raw3;

	tImages.push_back(&png);
	tImages.push_back(&png1);
	tImages.push_back(&png2);
	tImages.push_back(&png3);
	
	tImages.push_back(&jpg);
	tImages.push_back(&jpg1);
	tImages.push_back(&jpg2);
	tImages.push_back(&jpg3);

	tImages.push_back(&raw);
	tImages.push_back(&raw1);
	tImages.push_back(&raw2);
	tImages.push_back(&raw3);

	for (unsigned int i = 0; i < tImages.size(); ++i)
	{
		if (tImages[i]->hasAlpha)
		{
			CPNG* image = static_cast<CPNG*>(tImages[i]);
			image->RemoveAlpha();
		}
	}

	return 0;
}
