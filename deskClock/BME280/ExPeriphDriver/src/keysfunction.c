/******************************************************************************/
/** ģ�����ƣ�������������                                                   **/
/** �ļ����ƣ�keysfunction.c                                                 **/
/** ��    ����V1.0.0                                                         **/
/** ��    �飺ʵ�ֶ԰�����ɨ�����ȡ���Ե�������ϼ�������                   **/
/**--------------------------------------------------------------------------**/
/** �޸ļ�¼��                                                               **/
/**     �汾      ����              ����              ˵��                   **/
/**     V1.0.0  2012-07-28          ľ��              �����ļ�               **/
/******************************************************************************/ 

#include "stddef.h"
#include "keysfunction.h"

KeyStateQueueType keyState;

/*��ֵ�����г���*/
uint8_t KeyValueDeQueue(void)
{
  uint8_t result; 
	
  if(keyState.pRead==keyState.pWrite)
  {
    result=0;
  }
  else
  {
    result=keyState.queue[keyState.pRead];
 
    if(++keyState.pRead>=KEY_FIFO_SIZE)
    {
      keyState.pRead=0;
    }
  }
  return result;
}
	
/*��ֵ����г���*/
void KeyValueEnQueue(uint8_t keyCode)
{
  keyState.queue[keyState.pWrite]=keyCode;

  if(++keyState.pWrite >= KEY_FIFO_SIZE)
  {
    keyState.pWrite=0;
  }
} 

/*�����ֵ���г���*/
void ClearKeyValueQueue(void)
{
  keyState.pRead=keyState.pWrite;
}
	
/*��������ɨ�����*/
void KeyValueDetect(KeyObjectType *pKey)
{
  if (CheckKeyDown(pKey))
  {
    if (pKey->Count < KEY_FILTER_TIME)
    {
      pKey->Count = KEY_FILTER_TIME;
    }
    else if(pKey->Count < 2 * KEY_FILTER_TIME)
    {
      pKey->Count++;
    }
    else
    {
      if (pKey->State == 0)
      {
        pKey->State = 1;

        /*���Ͱ��������¼���Ϣ*/
        KeyValueEnQueue((uint8_t)((pKey->id<<2) + KeyDown));
      }

      if (pKey->LongTime > 0)
      {
        if (pKey->LongCount < pKey->LongTime)
        {
          /* ���Ͱ����������µ��¼���Ϣ */
          if (++pKey->LongCount == pKey->LongTime)
          {
            /* ��ֵ���밴��FIFO */
            KeyValueEnQueue((uint8_t)((pKey->id<<2) + KeyLong));
          }
        }
        else
        {
          if (pKey->RepeatPeriod > 0)
          {
            if (++pKey->RepeatCount >= pKey->RepeatPeriod)
            {
              pKey->RepeatCount = 0;
              /*��������ÿ��10ms����1������*/
              KeyValueEnQueue((uint8_t)((pKey->id<<2) + KeyDown));
            }
          }
        }
      }
    }
  }
  else
  {
    if(pKey->Count > KEY_FILTER_TIME)
    {
      pKey->Count = KEY_FILTER_TIME;
    }
    else if(pKey->Count != 0)
    {
      pKey->Count--;
    }
    else
    {
      if (pKey->State == 1)
      {
        pKey->State = 0;

        /*���Ͱ��������¼���Ϣ*/
        KeyValueEnQueue((uint8_t)((pKey->id<<2)+ KeyUP));
      }
    }

    pKey->LongCount = 0;
    pKey->RepeatCount = 0;
  }
}

/*������ȡ��ʼ��*/
void KeysInitialization(KeyObjectType *pKey,uint8_t id,uint16_t longTime, uint8_t repeatPeriod,KeyActiveLevelType level)
{
  if(pKey==NULL)
  {
    return;
  }
	
  pKey->id=id;
  pKey->Count=0;
  pKey->LongCount=0;
  pKey->RepeatCount=0;
  pKey->State=0;
  
  pKey->ActiveLevel=level;
  
  pKey->LongTime=longTime;
  pKey->RepeatPeriod=repeatPeriod;
}

/*���ĳ��ID�İ�����������ϼ����Ƿ���*/
__weak uint8_t CheckKeyDown(KeyObjectType *pKey)
{
  //��Ӳ����أ���Ӧ����ʵ��
  return 0;
}
/*********** (C) COPYRIGHT 1999-2019 Moonan Technology *********END OF FILE****/
