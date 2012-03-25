#ifndef __GVARIANT_H
#define __GVARIANT_H

#include "cpgf/gvartypedata.h"
#include "cpgf/gerrorcode.h"
#include "cpgf/gclassutil.h"
#include "cpgf/gifelse.h"

#include <string>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4127) // warning C4127: conditional expression is constant
#pragma warning(disable:4244)
#pragma warning(disable:4800) // warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning(disable:4267) // weird warning when reflecting std::vector in VC, disable it.
#endif

namespace cpgf {

struct VarantCastKeepConstRef {};
struct VarantCastCopyConstRef {};

class GVariant;
class GMetaVariant;

template <typename T>
bool canFromVariant(const GVariant & v);

namespace variant_internal {

template <bool Copyable, typename T>
void InitVariant(GVariant & v, const GVarTypeData & typeData, const typename RemoveReference<T>::Result & value);

class IVariantShadowObject;

struct GVariantDataHolder
{
	int a;
	int b;
	int c;
};


} // namespace variant_internal


inline bool vtIsEmpty(int vt) {
	return vt == vtEmpty;
}

inline bool vtIsFundamental(int vt) {
	return vt >= vtFundamentalBegin && vt <= vtFundamentalEnd;
}

inline bool vtIsBoolean(int vt) {
	return vt == vtBool;
}

inline bool vtIsInteger(int vt) {
	return vt >= vtIntegerBegin && vt <= vtIntegerEnd;
}

inline bool vtIsReal(int vt) {
	return vt >= vtFloat && vt <= vtLongDouble;
}

inline bool vtIsByPointer(int vt) {
	return (vt & byPointer) != 0;
}

inline bool vtIsByReference(int vt) {
	return (vt & byReference) != 0;
}

inline bool vtIsVoidPointer(int vt) {
	return vt == (byPointer | vtVoid);
}


#pragma pack(push, 1)
#pragma pack(1)
struct GVariantData
{
	GVarTypeData typeData;

	union {
		variant_internal::GVariantDataHolder holder;

		bool valueBool;
		char valueChar;
		wchar_t valueWchar;
		signed char valueSignedChar;
		unsigned char valueUnsignedChar;
		signed short valueSignedShort;
		unsigned short valueUnsignedShort;
		signed int valueSignedInt;
		unsigned int valueUnsignedInt;
		signed long valueSignedLong;
		unsigned long valueUnsignedLong;
		signed long long valueSignedLongLong;
		unsigned long long valueUnsignedLongLong;
		float valueFloat;
		double valueDouble;
		long double valueLongDouble;
		const volatile void * valuePointer;
		const volatile void * valueObject;

		const volatile bool * ptrBool;
		const volatile char * ptrChar;
		const volatile wchar_t * ptrWchar;
		const volatile signed char * ptrSignedChar;
		const volatile unsigned char * ptrUnsignedChar;
		const volatile signed short * ptrSignedShort;
		const volatile unsigned short * ptrUnsignedShort;;
		const volatile signed int * ptrSignedInt;
		const volatile unsigned int * ptrUnsignedInt;
		const volatile signed long * ptrSignedLong;
		const volatile unsigned long * ptrUnsignedLong;
		const volatile signed long long * ptrSignedLongLong;
		const volatile unsigned long long * ptrUnsignedLongLong;
		const volatile float * ptrFloat;
		const volatile double * ptrDouble;
		const volatile long double * ptrLongDouble;
		const volatile void * ptrPointer;
		const volatile void * ptrObject;
		
		variant_internal::IVariantShadowObject * shadowObject;
		IObject * valueInterface;
		IByteArray * valueByteArray;

	};
};
#pragma pack(pop)


GMAKE_FINAL(GVariant)

class GVariant : GFINAL_BASE(GVariant)
{
public:
	GVariant();
	GVariant(const GVariantData & data);

	template <typename T>
	GVariant(const T & value) {
		GVarTypeData typeData;
		vtInit(typeData);
		deduceVariantType<T>(typeData);
		variant_internal::InitVariant<true, typename variant_internal::DeducePassType<T>::PassType>(*this, typeData, value);
	}

	template <typename T>
	GVariant(const GVarTypeData & typeData, const T & value) {
		variant_internal::InitVariant<true, T>(*this, typeData, value);
	}

	GVariant(const GVariant & other);
	~GVariant();
	GVariant & operator = (GVariant other);
	void swap(GVariant & other);

	const GVarTypeData & getTypeData() const {
		return this->data.typeData;
	}

	GVariantType getType() const {
		return vtGetType(this->data.typeData);
	}

	GVariantType getBaseType() const {
		return vtGetBaseType(this->data.typeData);
	}

	int getPointers() const {
		return vtGetPointers(this->data.typeData);
	}

	bool isEmpty() const {
		return vtIsEmpty(this->getType());
	}

	GVariantData getData() const {
		return this->data;
	}

	GVariantData takeData();

private:
	void init();

public:
	GVariantData data;

private:
	GVariant(const GMetaVariant &); //disable
};

inline void swap(GVariant & a, GVariant & b)
{
	a.swap(b);
}

extern void raiseCoreException(int errorCode, ...);

void failedCast();
void checkFailCast(bool success);


#include "cpgf/private/gvariant_p.h"


template <typename T>
bool canFromVariant(const GVariant & v)
{
	return variant_internal::CanCastFromVariant<typename RemoveConstVolatile<T>::Result, VarantCastKeepConstRef>::canCast(vtGetType(v.data.typeData));
}

template <typename T, typename Policy>
bool canFromVariant(const GVariant & v)
{
	return variant_internal::CanCastFromVariant<typename RemoveConstVolatile<T>::Result, Policy>::canCast(vtGetType(v.data.typeData));
}

template <typename T>
typename variant_internal::CastFromVariant<T, VarantCastKeepConstRef>::ResultType fromVariant(const GVariant & v)
{
	return variant_internal::CastFromVariant<typename RemoveConstVolatile<T>::Result, VarantCastKeepConstRef>::cast(v);
}

template <typename T, typename Policy>
typename variant_internal::CastFromVariant<T, Policy>::ResultType fromVariant(const GVariant & v)
{
	return variant_internal::CastFromVariant<typename RemoveConstVolatile<T>::Result, Policy>::cast(v);
}

template <typename T>
GVariant pointerToRefVariant(T * p)
{
	GVariant v(p);

	if(vtIsByPointer(v.getType())) {
		vtSetType(v.data.typeData, (vtGetType(v.data.typeData) & ~byPointer) | byReference);
	}

	return v;
}

GVariant pointerToRefVariant(const GVariant & p);

template <bool Copyable, typename T>
GVariant createVariant(const T & value, bool copyObject = false)
{
	GVarTypeData typeData;
	deduceVariantType<T>(typeData, copyObject);
	GVariant v;
	variant_internal::InitVariant<Copyable, typename variant_internal::DeducePassType<T>::PassType>(v, typeData, value);
	return v;
}

template <typename T>
GVariant createVariantFromCopyable(const T & value)
{
	return createVariant<true>(value, false);
}

template <typename T>
GVariant copyVariantFromCopyable(const T & value)
{
	return createVariant<true>(value, true);
}

GVariant pointerToObjectVariant(void * p);
void * objectAddressFromVariant(const GVariant & v);
void * referenceAddressFromVariant(const GVariant & v);
void initializeVarData(GVariantData * data);
void freeVarData(GVariantData * data);
void initializeVarString(GVariantData * data, const char * s);
GVariant createStringVariant(const char * s);
bool variantIsString(const GVariant & v);
void initializeVarWideString(GVariantData * data, const wchar_t * s);
GVariant createWideStringVariant(const wchar_t * s);
bool variantIsWideString(const GVariant & v);


} // namespace cpgf


#if defined(_MSC_VER)
#pragma warning(pop)
#endif


#endif

