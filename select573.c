#include "select573.h"
void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80;  //����λ���㣺0001 1111 ����λ1000 0000
			break;
		case 5:
			P2=(P2&0x1f)|0xa0;  //����λ���㣺0001 1111 ����λ1010 0000
			break;
		case 6:
			P2=(P2&0x1f)|0xc0;  //����λ���㣺0001 1111 ����λ1100 0000
			break;
		case 7:
			P2=(P2&0x1f)|0xe0;  //����λ���㣺0001 1111 ����λ1110 0000
			break;
		case 0:
			P2=(P2&0x1f)|0x00;
		  break;
	}
}