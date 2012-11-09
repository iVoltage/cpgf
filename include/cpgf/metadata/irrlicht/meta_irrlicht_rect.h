// Auto generated file, don't modify.

#ifndef __META_IRRLICHT_RECT_H
#define __META_IRRLICHT_RECT_H


#include "gmetaobjectlifemanager_irrlicht_ireferencecounted.h"
#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace irr;
using namespace irr::core;


namespace meta_irrlicht { 


template <typename D>
void buildMetaClass_Global_rect(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
}


template <typename D, typename T>
void buildMetaClass_Rect(const cpgf::GMetaDataConfigFlags & config, D _d)
{
    (void)config; (void)_d; (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (T, T, T, T)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const position2d< T > &, const position2d< T > &)>();
    _d.CPGF_MD_TEMPLATE _field("UpperLeftCorner", &D::ClassType::UpperLeftCorner);
    _d.CPGF_MD_TEMPLATE _field("LowerRightCorner", &D::ClassType::LowerRightCorner);
    _d.CPGF_MD_TEMPLATE _method("getArea", &D::ClassType::getArea);
    _d.CPGF_MD_TEMPLATE _method("isPointInside", &D::ClassType::isPointInside);
    _d.CPGF_MD_TEMPLATE _method("isRectCollided", &D::ClassType::isRectCollided);
    _d.CPGF_MD_TEMPLATE _method("clipAgainst", &D::ClassType::clipAgainst);
    _d.CPGF_MD_TEMPLATE _method("constrainTo", &D::ClassType::constrainTo);
    _d.CPGF_MD_TEMPLATE _method("getWidth", &D::ClassType::getWidth);
    _d.CPGF_MD_TEMPLATE _method("getHeight", &D::ClassType::getHeight);
    _d.CPGF_MD_TEMPLATE _method("repair", &D::ClassType::repair);
    _d.CPGF_MD_TEMPLATE _method("isValid", &D::ClassType::isValid);
    _d.CPGF_MD_TEMPLATE _method("getCenter", &D::ClassType::getCenter);
    _d.CPGF_MD_TEMPLATE _method("getSize", &D::ClassType::getSize);
    _d.CPGF_MD_TEMPLATE _method("addInternalPoint", (void (D::ClassType::*) (const position2d< T > &))&D::ClassType::addInternalPoint);
    _d.CPGF_MD_TEMPLATE _method("addInternalPoint", (void (D::ClassType::*) (T, T))&D::ClassType::addInternalPoint);
    _d.CPGF_MD_TEMPLATE _operator<rect< T > (*)(const cpgf::GMetaSelf &, const position2d< T > &)>(mopHolder + mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<rect< T > & (*)(cpgf::GMetaSelf, const position2d< T > &)>(mopHolder += mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<rect< T > (*)(const cpgf::GMetaSelf &, const position2d< T > &)>(mopHolder - mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<rect< T > & (*)(cpgf::GMetaSelf, const position2d< T > &)>(mopHolder -= mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const rect< T > &)>(mopHolder == mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const rect< T > &)>(mopHolder != mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const cpgf::GMetaSelf &, const rect< T > &)>(mopHolder < mopHolder);
}


} // namespace meta_irrlicht




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif