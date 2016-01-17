#if !defined DISMAP_HXX
#define DISMAP_HXX

#include <pthread.h>
#include <map>
#include <DIS/EntityStatePdu.h>

//////////////////////////////////////////////////////////////////////
/**
 * @class PDUList
 * @brief Threadsafe Map for EntitystatePDUs
 */

class PDUList : public std::map<std::string, DIS::EntityStatePdu>
{
	public:
		PDUList( void );
		~PDUList( void );
		/** thread lock the list */
		void Lock();
		/** thread unlock the list */
		void Unlock();
		/** delete all elements of this list */
		void   Clear ();

	protected:

		/** @brief mutex for thread safty */
		pthread_mutex_t   m_MapMutex;
};//PDUList

#endif