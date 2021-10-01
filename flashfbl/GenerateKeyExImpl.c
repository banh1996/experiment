#include "KeyGenAlgoInterfaceEx.h"


void VKeyGenResultEx_t GenerateKeyEx(
      const unsigned char*  iSeedArray,     /* Array for the seed [in] */
      unsigned int          iSeedArraySize, /* Length of the array for the seed [in] */
      const unsigned int    iSecurityLevel, /* Security level [in] */
      const char*           iVariant,       /* Name of the active variant [in] */
      unsigned char*        ioKeyArray,     /* Array for the key [in, out] */
      unsigned int          iKeyArraySize,  /* Maximum length of the array for the key [in] */
      unsigned int*         oSize           /* Length of the key [out] */
      )
{
    if (iSeedArraySize>iKeyArraySize)
      return KGRE_BufferToSmall;
    for (unsigned int i = 0; i < iSeedArraySize; i++)
    {
        if (iSecurityLevel == 0x1)
        {
            ioKeyArray[i] = 0x11;// ~iSeedArray[i];
        }
        else if (iSecurityLevel == 0x3)
        {
            ioKeyArray[i] = 0x33;// ~iSeedArray[i];
        }
        else if(iSecurityLevel == 0x5)
        {
            ioKeyArray[i] = 0x55;// ~iSeedArray[i];
        }
        else if (iSecurityLevel == 0x7)
        {
            ioKeyArray[i] = 0x77;// ~iSeedArray[i];
        }     
    }
    *oSize=iSeedArraySize;
    
  return KGRE_Ok;
}
