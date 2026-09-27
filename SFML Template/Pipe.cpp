#include "Pipe.h"

namespace ShowTime
{
	Pipe::Pipe(GameDataRef data) : data(data)
	{

	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			data->window.draw(*pipeSprites.at(i));
		}
	}
}