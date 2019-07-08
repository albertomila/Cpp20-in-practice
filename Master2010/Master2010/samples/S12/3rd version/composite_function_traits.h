#pragma once
#include "stdafx.h"
#include "samples/S11/S11.metaprogramation.h"

template <class, class>
   class compose_fx_gx_impl;
template <class, class>
   class fx_then_gx_impl;

template <class>
   struct composite_function_traits;
template <class FX, class GX>
   struct composite_function_traits<
      compose_fx_gx_impl<FX, GX>
   >
   {
      typedef FX function_0_type;
      typedef GX function_1_type;
   };
template <class FX, class GX>
   struct composite_function_traits<
      fx_then_gx_impl<FX, GX>
   >
   {
      typedef FX function_0_type;
      typedef GX function_1_type;
   };

template <class>
   struct is_composite_function
   {
      static const bool VAL = false;
   };
template <class FX, class GX>
   struct is_composite_function<
      compose_fx_gx_impl<FX, GX>
   >
   {
      static const bool VAL = true;
   };
template <class FX, class GX>
   struct is_composite_function<
      fx_then_gx_impl<FX, GX>
   >
   {
      static const bool VAL = true;
   };


template <class C, class F>
   struct possesses_function
   {
   private:
      struct not_composite_function
      {
         static const bool VAL = false;
      };
      template <class U>
         struct recursive_possesses_function_impl
         {
            typedef
              composite_function_traits<U> traits_U;
            static const bool VAL = meme_type<
               typename traits_U::function_0_type, F
            >::VAL || meme_type<
               typename traits_U::function_1_type, F
            >::VAL || possesses_function<
               typename traits_U::function_0_type, F
            >::VAL || possesses_function<
               typename traits_U::function_1_type, F
            >::VAL;
         };
      template <class U>
         struct recursive_possesses_function
            : static_if_else<
                 is_composite_function<U>::VAL,
                 recursive_possesses_function_impl<U>,
                 not_composite_function
            >::type
         {
         };
   public:
      static const bool VAL =
         recursive_possesses_function<C>::VAL;
   };

template <class F0, class F1, class T>
   struct composite_function_child_selector
   {
      typedef typename
         static_if_else<
            possesses_function<F0, T>::VAL,
            F0,
            F1
         >::type type;
   };