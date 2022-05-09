#include "AudioBuffer.h"

#include <fstream>

#include "stdint.h"

#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "../openal/AL/efx.h"
#include "../openal/AL/efx-creative.h"
#include "../openal/AL/efx-presets.h"


ALuint AudioBuffer::getAlBuffer() const
{ 
	return m_uBufferID;  
}

AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, &m_uBufferID);
}


AudioBuffer* AudioBuffer::load(const char* _pFilename)
{
	ALuint bufferID;
	alGenBuffers(1, &bufferID);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("ERROR: GenBuffers\n");
		return nullptr;
	}
	FILE* pFile = fopen(_pFilename, "r");
	if (!pFile)
	{
		printf("ERROR: No se pudo abrir el fichero %s\n", _pFilename);
		return nullptr;
	}

	char cBuffer[5] = "";
	//Leer a ver si pone RIFF lo primero
	fread(cBuffer, sizeof(char), 4, pFile);
	if (strcmp(cBuffer, "RIFF") != 0)
	{
		printf("ERROR: %s no es un Was\n", _pFilename);
		return nullptr;
	}
	//Skip 12 chars
	fread(cBuffer, sizeof(char), 4, pFile);
	fread(cBuffer, sizeof(char), 4, pFile);
	fread(cBuffer, sizeof(char), 4, pFile);
	//Read FMTChunkSize (only one byte will have useful information, but could be first or last)
	fread(cBuffer, sizeof(char), 4, pFile);
	int iFmtChunkSize = cBuffer[3] << 24 | cBuffer[2] << 16 | cBuffer[1] << 8 | cBuffer[0];
	//Read AudioFormat (only one byte will have useful information, but could be first or last)
	fread(cBuffer, sizeof(char), 2, pFile);
	int iAudioFormat = cBuffer[1] << 8 | cBuffer[0];
	//Read numChannels (only one byte will have useful information, but could be first or last)
	fread(cBuffer, sizeof(char), 2, pFile);
	int iChannels = cBuffer[1] << 8 | cBuffer[0];
	//Read frequency (only one byte will have useful information, but could be first or last)
	fread(cBuffer, sizeof(char), 4, pFile);
	ALsizei iFreq = cBuffer[3] << 24 | cBuffer[2] << 16 | cBuffer[1] << 8 | cBuffer[0];
	//Skip 6 bytes
	fread(cBuffer, sizeof(char), 4, pFile);
	fread(cBuffer, sizeof(char), 2, pFile);
	//Read bits per sample (only one byte will have useful information, but could be first or last)
	fread(cBuffer, sizeof(char), 2, pFile);
	int iBitsPerSample = cBuffer[1] << 8 | cBuffer[0];
	//Si no es un fichero comprimido, leer valores extra
	if (iAudioFormat != 1 && iFmtChunkSize > 16)
	{
		fread(cBuffer, sizeof(char), 2, pFile);
		int iExtraParamsSize = cBuffer[1] << 8 | cBuffer[0];
		fread(cBuffer, sizeof(char), iExtraParamsSize, pFile);
	}
	//Buscar "data" en el archivo, tiene que buscarse asi porque puede estar ddata o leer solo la mitad de la palabra
	bool bDataFind = false;
	while (!bDataFind)
	{
		fread(cBuffer, sizeof(char), 1, pFile);
		if (strcmp(cBuffer, "d") == 0)
		{
			fread(cBuffer, sizeof(char), 1, pFile);
			if (strcmp(cBuffer, "a") == 0)
			{
				fread(cBuffer, sizeof(char), 1, pFile);
				if (strcmp(cBuffer, "t") == 0)
				{
					fread(cBuffer, sizeof(char), 1, pFile);
					if (strcmp(cBuffer, "a") == 0)
					{
						bDataFind = true;
					}
				}
			}
		}
	}
	//Read frequency (only one byte will have useful information, but could be first or last)
	fread(cBuffer, sizeof(char), 4, pFile);
	unsigned int iDataSize = static_cast<unsigned char>(cBuffer[3]) << 24 | static_cast<unsigned char>(cBuffer[2]) << 16 | static_cast<unsigned char>(cBuffer[1]) << 8 | static_cast<unsigned char>(cBuffer[0]);
	//Crear array del tamaño de la data del audio
	char* pData = new char[iDataSize];

	//Read the full remaining data of the file which contains the audio 
	fread(pData, sizeof(char), iDataSize, pFile);
	ALenum eFormatBuffer = (iBitsPerSample == 8) ? 
		(iChannels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8) :
		(iChannels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
	//Place the file info in the buffer
	alBufferData(bufferID, eFormatBuffer, pData, iDataSize, iFreq);
	
	//Because the that is in the buffer, delete array
	delete[]pData;
	fclose(pFile);

	return new AudioBuffer(bufferID);
}
