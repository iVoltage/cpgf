#ifndef __GSCRIPTWRAPPER_H
#define __GSCRIPTWRAPPER_H


#include "cpgf/metatraits/gmetascriptwrapper.h"
#include "cpgf/gapi.h"
#include "cpgf/gtypetraits.h"


namespace cpgf {

struct IScriptFunction;

struct IScriptDataStorage : public IObject
{
	virtual IScriptFunction * G_API_CC getScriptFunction(const char * name) = 0;
};

class GScriptWrapper
{
public:
	GScriptWrapper();

	IScriptFunction * getScriptFunction(const char * name) const;

	void setScriptDataStorage(IScriptDataStorage * scriptDataStorage);

private:
	GSharedInterface<IScriptDataStorage> scriptDataStorage;
};

class GScriptWrapperReentryGuard
{
public:
	explicit GScriptWrapperReentryGuard(bool * sentinel) : sentinel(sentinel) {
		*sentinel = true;
	}

	~GScriptWrapperReentryGuard() {
		*sentinel = false;
	}

private:
	bool * sentinel;
};

namespace scriptbind_internal {

	typedef void * (*CasterType)(void *);

	template <typename From, typename To>
	struct InstanceCaster
	{
		static void * cast(void * instance) {
			return static_cast<To *>(static_cast<From *>(instance));
		}
	};

	IMetaScriptWrapper * doCreateScriptWrapper(CasterType caster);

} // namespace scriptbind_internal

template <typename T>
IMetaScriptWrapper * metaTraitsCreateScriptWrapper(const GMetaTraitsParam &, typename GEnableIfResult<IsConvertible<const T &, const GScriptWrapper &>, GScriptWrapper >::Result *)
{
	return scriptbind_internal::doCreateScriptWrapper(&scriptbind_internal::InstanceCaster<T, GScriptWrapper>::cast);
}



} // namespace cpgf



#endif