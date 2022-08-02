#include "DomainValidator.h"

void ValidatorTrenchCoat::validate_quantity(const TrenchCoat& trench_coat) {
	if (trench_coat.get_quantity() < MIN_QUANTITY || trench_coat.get_quantity() > MAX_QUANTITY) {
		throw Exception{ 1, "Invalid quantity" };
	}
}

void ValidatorTrenchCoat::validate_size(const TrenchCoat& trench_coat) {
	if (trench_coat.get_size() < MIN_SIZE || trench_coat.get_size() > MAX_SIZE) {
		throw Exception{ 1, "Invalid size" };
	}
}

void ValidatorTrenchCoat::validate_price(const TrenchCoat& trench_coat) {
	if (trench_coat.get_price() < MIN_PRICE || trench_coat.get_size() > MAX_PRICE) {
		throw Exception{ 1, "Invalid price" };
	}
}

void ValidatorTrenchCoat::validate_color(const TrenchCoat& trench_coat) {
	vector<string> colors = {
	"indianred","lightcoral","salmon" ,"darksalmon" ,"lightsalmon" ,"crimson" ,"red" ,"firebrick",
	"darkred" ,"pink" ,"lightpink" ,"hotpink" ,"deeppink" ,"mediumvioletred" ,"paleVioletred",
	"lightsalmon" ,"coral" ,"tomato" ,"orangered" ,"darkorange" ,"orange" ,"gold" ,"yellow",
	"lightyellow" ,"lemonchiffon" ,"lightgoldenrodyellow" ,"papayawhip" ,"moccasin" ,"peachpuff",
	"palegoldenrod" ,"khaki" ,"darkkhaki" ,"lavender" ,"thistle" ,"plum" ,"violet" ,"orchid",
	"fuchsia" ,"magenta" ,"mediumorchid" ,"mediumpurple" ,"rebeccapurple" ,"blueviolet",
	"darkviolet" ,"darkorchid" ,"darkmagenta" ,"purple" ,"indigo" ,"slateblue" ,"darkslateblue",
	"mediumslateblue" ,"greenyellow" ,"chartreuse" ,"lawngreen" ,"lime" ,"limegreen",
	"palegreen" ,"lightgreen" ,"mediumspringgreen" ,"springgreen" ,"mediumseagreen",
	"seagreen" ,"forestgreen" ,"green" ,"darkgreen" ,"yellowgreen" ,"olivedrab" ,"olive",
	"darkolivegreen" ,"mediumaquamarine" ,"darkseagreen" ,"lightseagreen" ,"darkcyan",
	"teal" ,"aqua" ,"cyan" ,"lightcyan" ,"paleturquoise" ,"aquamarine" ,"turquoise" ,"mediumturquoise",
	"darkturquoise" ,"cadetblue" ,"steelblue" ,"lightsteelblue" ,"powderblue" ,"lightblue" ,"skyblue",
	"lightskyblue" ,"deepskyblue" ,"dodgerblue" ,"cornflowerblue" ,"mediumslateblue" ,"royalblue",
	"blue" ,"mediumblue" ,"darkblue" ,"navy" ,"midnightblue" ,"cornsilk" ,"blanchedalmond",
	"bisque" ,"navajowhite" ,"wheat" ,"burlywood" ,"tan" ,"rosybrown" ,"sandybrown" ,"goldenrod",
	"darkgoldenrod" ,"peru" ,"chocolate" ,"saddlebrown" ,"sienna" ,"brown" ,"maroon",
	"white" ,"snow" ,"honeydew" ,"mintcream" ,"azure" ,"aliceblue" ,"ghostwhite" ,"whitesmoke",
	"seashell" ,"beige" ,"oldlace" ,"floralwhite" ,"ivory" ,"antiquewhite" ,"linen",
	"lavenderblush" ,"mistyrose" ,"gainsboro" ,"lightgray" ,"silver" ,"darkgray" ,"gray", "grey",
	"dimgray" ,"lightslategray" ,"slategray" ,"darkslategray" ,"black" };
	for (const auto& color : colors) {
		if (color == trench_coat.get_color()) {
			return;
		}
	}
	throw Exception{ 1, "Invalid color" };
}

void ValidatorTrenchCoat::validate_photo(const TrenchCoat& trench_coat) {
	if (trench_coat.get_photo().size() < MIN_PHOTO_LENGTH) {
		throw Exception{ 1, "Invalid photo" };
	}
}

void ValidatorTrenchCoat::validate(const TrenchCoat& trench_coat) {
	validate_quantity(trench_coat);
	validate_size(trench_coat);
	validate_price(trench_coat);
	validate_color(trench_coat);
	validate_photo(trench_coat);
}
