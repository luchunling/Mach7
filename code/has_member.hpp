#pragma once

///
/// We use here code by Jason Shirk and Alexey Gurtovoy for detecting presence
/// of a given member. See the following discussion for details:
/// http://lists.boost.org/Archives/boost/2002/03/27251.php
///

typedef char (& no_tag)[1];
typedef char (&yes_tag)[2]; 

#ifdef _MSC_VER
// In the version for MSVC the member name has to be taken into ()
#define HAS_MEMBER_XXX(name,member_type,member_name) \
template < typename T, member_type > struct ptmf_##name##_helper {}; \
template < typename T > no_tag  has_member_##name##_helper(...); \
template < typename T > yes_tag has_member_##name##_helper(ptmf_##name##_helper<T, &(T::member_name)>* p); \
template < typename T > \
struct has_member_##name \
{ \
    static const bool value = sizeof(has_member_##name##_helper<T>(0)) == sizeof(yes_tag); \
}
#else
// In the version for GCC () around member name don't work for some reason, but note to keep space before >
#define HAS_MEMBER_XXX(name,member_type,member_name) \
template < typename T, member_type > struct ptmf_##name##_helper {}; \
template < typename T > no_tag  has_member_##name##_helper(...); \
template < typename T > yes_tag has_member_##name##_helper(ptmf_##name##_helper<T, &T::member_name >* p); \
template < typename T > \
struct has_member_##name \
{ \
    static const bool value = sizeof(has_member_##name##_helper<T>(0)) == sizeof(yes_tag); \
}
#endif

// Helpers to detect some unary operators

HAS_MEMBER_XXX(kind_selector, bool (T::*)() const, kind_selector_dummy);