#include <UDRefl/UDRefl.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::UDRefl;

enum class Color {
	Red,
	Green,
	Blue
};

int main() {
	ReflMngr::Instance().RegisterTypeAuto<Color>();
	ReflMngr::Instance().AddField<Color::Red>("Red");
	ReflMngr::Instance().AddField<Color::Green>("Green");
	ReflMngr::Instance().AddField<Color::Blue>("Blue");

	ReflMngr::Instance().ForEachRVar(
		TypeID_of<Color>,
		[](TypeRef type, FieldRef field, ConstObjectPtr var) {
			std::cout
				<< ReflMngr::Instance().nregistry.Nameof(field.ID)
				<< ": " << static_cast<int>(var.As<Color>())
				<< std::endl;
			return true;
		}
	);

	// enumerator -> name
	Color c = Color::Red;
	auto c_field = ReflMngr::Instance().FindField(TypeID::of<Color>, [c](FieldRef field) {
		return field.info.fieldptr.RVar() == c;
	});

	std::cout << "name of " << static_cast<int>(c) << " : " << ReflMngr::Instance().nregistry.Nameof(c_field.value().ID) << std::endl;

	// name -> enumerator
	std::string_view name = "GREEN";
	auto name_field = ReflMngr::Instance().FindField(TypeID_of<Color>, [name](FieldRef field) {
		return ReflMngr::Instance().nregistry.Nameof(field.ID) == name;
	});

	std::cout << "value of " << name << " : " << static_cast<int>(name_field.value().info.fieldptr.RVar().As<Color>()) << std::endl;
}
