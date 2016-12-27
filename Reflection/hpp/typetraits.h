#ifndef ZHIHE_TypeTraits_h__
#define ZHIHE_TypeTraits_h__
namespace zhihe
{
	//------------------------------------------------------------------------------
	template <class T>
	struct ContainerTraits
	{
		typedef bool isNotContainer;
	};
	struct TypeTraits
	{
		template <typename T>
		class isContainer
		{
		private:
			typedef char yes[1]; // sizeof (yes) == 1
			typedef char no[2]; // sizeof (no)  == 2

			template <typename C>
			static no& test(typename C::isNotContainer*);

			template <typename>
			static yes& test(...);

		public:
			static const bool value = sizeof(test <ContainerTraits <T> >(0)) == sizeof(yes);
		};
	};
	template <class T>
	struct isConst
	{
		static bool const value = false;
	};

	template <class T>
	struct isConst <T const>
	{
		static bool const value = true;
	};
	template <class T>
	struct removePointer
	{
		typedef T Type;
	};
	template <class T>
	struct removePointer<T*>
	{
		typedef T Type;
	};
	template <class T>
	struct removeConst
	{
		typedef T Type;
	};

	template <class T>
	struct removeConst <const T>
	{
		typedef T Type;
	};
	template <class T>
	struct removeConst <const T&>
	{
		typedef T& Type;
	};
	template <class T>
	struct removeConst <const T*>
	{
		typedef T* Type;
	};
	template <class T>
	struct convertConstRef
	{
		typedef T Type;
	};

	template <class T>
	struct convertConstRef <const T>
	{
		typedef T Type;
	};
	template <class T>
	struct convertConstRef <const T&>
	{
		typedef T* Type;
	};
	template <class T>
	struct convertConstRef <T&>
	{
		typedef T* Type;
	};
	template <class T>
	struct convertConstRef <const T*>
	{
		typedef T* Type;
	};
}
#endif
