#include "cpgf/gmetamethod.h"
#include "cpgf/gmetaclass.h"


#define REF_CALL_LOAD_PARAM(N, unused) params[N] = & p ## N;

#define REF_CALL_METHOD(N, unused) \
	GVariant GMetaMethod::invoke(void * instance GPP_COMMA_IF(N) GPP_REPEAT(N, GPP_COMMA_PARAM, const GVariant & p)) const { \
		const GVariant * params[REF_MAX_ARITY]; \
		GPP_REPEAT(N, REF_CALL_LOAD_PARAM, GPP_EMPTY); \
		return this->baseData->invoke(instance, params, N); \
	}

#define REF_NEW_INSTANCE(N, unused) \
	void * GMetaConstructor::invoke(GPP_REPEAT(N, GPP_COMMA_PARAM, const GVariant & p)) const { \
		const GVariant * params[REF_MAX_ARITY]; \
		GPP_REPEAT(N, REF_CALL_LOAD_PARAM, GPP_EMPTY); \
		return fromVariant<void *>(this->baseData->invoke(NULL, params, N)); \
	}

namespace cpgf {



GMetaType GMetaMethod::getParamType(size_t index) const
{
	return this->baseData->getParamType(index);
}

size_t GMetaMethod::getParamCount() const
{
	return this->baseData->getParamCount();
}

bool GMetaMethod::hasResult() const
{
	return this->baseData->hasResult();
}

GMetaType GMetaMethod::getResultType() const
{
	return this->baseData->getResultType();
}

bool GMetaMethod::isVariadic() const
{
	return this->baseData->isVariadic();
}

GVariant GMetaMethod::execute(void * instance, const GVariant * params, size_t paramCount) const
{
	GASSERT_MSG(paramCount <= REF_MAX_ARITY, "Too many parameters.");

	const cpgf::GVariant * variantPointers[REF_MAX_ARITY];

	for(size_t i = 0; i < paramCount; ++i) {
		variantPointers[i] = &params[i];
	}

	return this->baseData->invoke(instance, variantPointers, paramCount);
}

bool GMetaMethod::checkParam(const GVariant & param, size_t paramIndex) const
{
	return this->baseData->checkParam(param, paramIndex);
}

bool GMetaMethod::isParamTransferOwnership(size_t paramIndex) const
{
	return this->baseData->isParamTransferOwnership(paramIndex);
}

bool GMetaMethod::isResultTransferOwnership() const
{
	return this->baseData->isResultTransferOwnership();
}

GMetaConverter * GMetaMethod::createResultConverter() const
{
	return this->baseData->createResultConverter();
}

GPP_REPEAT_2(REF_MAX_ARITY, REF_CALL_METHOD, GPP_EMPTY)



GMetaType GMetaConstructor::getParamType(size_t index) const
{
	return this->baseData->getParamType(index);
}

size_t GMetaConstructor::getParamCount() const
{
	return this->baseData->getParamCount();
}

bool GMetaConstructor::hasResult() const
{
	return true;
}

GMetaType GMetaConstructor::getResultType() const
{
	GASSERT_MSG(metaIsClass(this->getOwnerItem()->getCategory()), "Constructor must be owned by class.");

	GMetaType type = static_cast<const GMetaClass *>(this->getOwnerItem())->getMetaType();

	type.addPointer();

	return type;
}

bool GMetaConstructor::isVariadic() const
{
	return this->baseData->isVariadic();
}

GVariant GMetaConstructor::execute(void * instance, const GVariant * params, size_t paramCount) const
{
	GASSERT_MSG(paramCount <= REF_MAX_ARITY, "Too many parameters.");

	(void)instance;

	const cpgf::GVariant * variantPointers[REF_MAX_ARITY];

	for(size_t i = 0; i < paramCount; ++i) {
		variantPointers[i] = &params[i];
	}

	return this->baseData->invoke(NULL, variantPointers, paramCount);
}

bool GMetaConstructor::checkParam(const GVariant & param, size_t paramIndex) const
{
	return this->baseData->checkParam(param, paramIndex);
}

bool GMetaConstructor::isParamTransferOwnership(size_t paramIndex) const
{
	return this->baseData->isParamTransferOwnership(paramIndex);
}

bool GMetaConstructor::isResultTransferOwnership() const
{
	return this->baseData->isResultTransferOwnership();
}

GMetaConverter * GMetaConstructor::createResultConverter() const
{
	return NULL;
}

GPP_REPEAT_2(REF_MAX_ARITY, REF_NEW_INSTANCE, GPP_EMPTY)



} // namespace cpgf
