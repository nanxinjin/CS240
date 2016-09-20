
#include "Sound.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/stat.h"


Sound::Sound(int numChannels, int sampleRate, int bitsPerSample){
	this->sampleRate = sampleRate;
	this->numChannels = numChannels;
	this->bytesPerSample = bitsPerSample/8;
	this->bitsPerSample = bitsPerSample;
	this->lastSample = 0;
	this->maxSamples = 30000;
	this->dataSize = 0;
	this->fileSize = 0;
	hdr = (WaveHeader*)malloc(sizeof(WaveHeader)- 1 + maxSamples*bytesPerSample);
}

Sound::~Sound(){
	delete hdr;
}

int
Sound::getLittleEndian4(unsigned char * dest){
	int val;
	val = dest[0] + (dest[1]<<8) + (dest[2]<<16) + (dest[3]<<24);
	return val;
}

void
Sound::assignLittleEndian4(unsigned char * dest, unsigned int  value)
{
	dest[0] = value & 0xFF;
	dest[1] = (value>>8) & 0xFF;
	dest[2] = (value>>16) & 0xFF;
	dest[3] = (value>>24) & 0xFF;
}

bool
Sound::read(const char * fileName) {
	FILE * f = fopen(fileName, "r");
	if (f == NULL){
		return false;
	}
	struct  stat  buf;
	stat(fileName, &buf);
	int fsize = buf.st_size;

	WaveHeader * hdr = (WaveHeader *) malloc(fsize+1);

	fread( hdr, fsize, 1, f);
	fclose(f);

	this->numChannels = hdr->numChannels[0];
	this->sampleRate = getLittleEndian4(hdr->sampleRate);
	this->bitsPerSample = hdr->bitsPerSample[0]+(hdr->bitsPerSample[1]<<8);
	this->bytesPerSample = (this->bitsPerSample/8)*this->numChannels;
	this->hdr =  hdr;
	this->lastSample = getLittleEndian4(hdr->subchunk2Size)/this->bytesPerSample;
	this->maxSamples = this->lastSample;

	return true;
}


void
Sound::write(const char*fileName){
	dataSize = bytesPerSample * lastSample;
	fileSize = sizeof(WaveHeader) - 1 + dataSize;

	hdr->chunkID[0]='R'; hdr->chunkID[1]='I'; hdr->chunkID[2]='F'; hdr->chunkID[3]='F';
	assignLittleEndian4(hdr->chunkSize, fileSize - 8);
	hdr->format[0] = 'W'; hdr->format[1] = 'A'; hdr->format[2] = 'V'; hdr->format[3] = 'E';
	hdr->subchunk1ID[0]='f'; hdr->subchunk1ID[1]='m'; hdr->subchunk1ID[2]='t'; hdr->subchunk1ID[3]=' ';
	assignLittleEndian4( hdr->subchunk1Size,16);
	hdr->audioFormat[0] = 1; hdr->audioFormat[1]=0;
	hdr->numChannels[0] = numChannels; hdr->numChannels[1]=0;
	assignLittleEndian4(hdr->sampleRate, sampleRate);
	assignLittleEndian4(hdr->byteRate, numChannels * sampleRate * bitsPerSample/8);
	hdr->blockAlign[0] = numChannels * bitsPerSample/8; hdr->blockAlign[1]=0;
	hdr->bitsPerSample[0] = bitsPerSample; hdr->bitsPerSample[1]=0;
	hdr->subchunk2ID[0]='d'; hdr->subchunk2ID[1]='a'; hdr->subchunk2ID[2]='t'; hdr->subchunk2ID[3]='a';
	assignLittleEndian4(hdr->subchunk2Size, dataSize);

	FILE * f = fopen(fileName, "w+");
	fwrite(hdr,fileSize,1,f);
	fclose(f);

}

void 
Sound::add_sample(int sample){

	int littleE = 0;
	int test = 5;
	if(*(char*)&test == 5){
		littleE = 1;
	}

	if(maxSamples == lastSample){
		maxSamples += 550;
		hdr = (WaveHeader *)realloc(hdr,sizeof(WaveHeader)- 1+ maxSamples*bytesPerSample);
	}

	int sValue = sample;
	if(littleE){
		hdr->data[2*lastSample + 1] = *((unsigned char*)&sValue + 1);
		hdr->data[2*lastSample] = *((unsigned char*)&sValue);
	}else{
		hdr->data[2*lastSample + 1] = *((unsigned char*)&sValue);
		hdr->data[2*lastSample] = *((unsigned char*)&sValue + 1);
	}

	lastSample ++;
}



int 
Sound::get_sample(int i){
	int a = 5;
	int val;
	int littleE = 0;
	if(*(char*)&a == 5){
		littleE = 1;
	}
	if(littleE){
		*((unsigned char*)&val + 1) = hdr->data[2*i + 1];
		*((unsigned char*)&val) = hdr->data[2*i];
	}else{
		*((unsigned char*)&val) = hdr->data[2*i + 1];
		*((unsigned char*)&val + 1) = hdr->data[2*i];
	}
	return val;
}

void
Sound::append(Sound *src){
	int s;
	int a = 0;
	for(a = 0; a<src->maxSamples;a++){
		s = src->get_sample(a);
		add_sample(s);
	}
}
