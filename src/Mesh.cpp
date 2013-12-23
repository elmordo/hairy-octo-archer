/*
 * Mesh.cpp
 *
 *  Created on: 13.9.2013
 *      Author: petr
 */

#include "Mesh.hpp"

namespace Gremlin {
namespace Mesh {

Mesh::Mesh() {
	// TODO Auto-generated constructor stub

}

Mesh::Mesh(const Mesh& o) : GraphicData(o) {
	// kopirovani puvodniho objektu
	vg = o.vg;
}

Mesh::~Mesh() {
	// TODO Auto-generated destructor stub
}

size_t Mesh::addVGroup() {
	// navratova hodnota je aktualni pocet skupin
	size_t retVal = vg.size();

	// vlozeni prazdne skupiny
	vg.push_back(VertexGroup());

	return retVal;
}

VertexGroup& Mesh::VGroup(size_t index) {
	// iterace na dany index
	VGList::iterator pos = vg.begin();

	for (size_t i = 0;
			i < index;
			i++, pos++);

	return *pos;
}

const VertexGroup& Mesh::VGroup(size_t index) const {
	// iterace na dany index
	VGList::const_iterator pos = vg.begin();

	for (size_t i = 0;
			i < index;
			i++, pos++);

	return *pos;
}

void Mesh::removeVGroup(size_t index) {
	// iterace na dany index
	VGList::iterator pos = vg.begin();

	for (size_t i = 0;
			i < index;
			i++, pos++);

	// odstraneni iteratoru
	vg.erase(pos);
}

size_t Mesh::VGCount() {
	return vg.size();
}

size_t Mesh::materialCount() const {
	return vg.size();
}

void Mesh::render(const MaterialMap &mats) const {
	// index aktualni skupiny
	size_t index = 0;

	// pomocny seznam materialu pro predavani vertexgrupe pri renderu
	MaterialMap localMats;

	// iterace nad skupinami a jejich vykresleni
	for (VGList::const_iterator pos = vg.begin(); pos != vg.end(); pos++, index++) {
		// vyhodnoceni materialu

		// pokud index v danem seznamu existuje, zapise se
		MaterialMap::const_iterator matPos = mats.find(index);

		if (matPos != mats.end()) {
			localMats[0] = matPos->second;
		} else {
			localMats[0] = 0x0;
		}


		pos->render(localMats);
	}
}

} /* namespace Mesh */
} /* namespace Gremlin */
