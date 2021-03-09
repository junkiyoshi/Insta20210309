#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	int span = 2;
	for (int y = -200; y <= 200; y += 200) {

		for (int x = -150; x <= 150; x += 5) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(x, -50, 0));
			vertices.push_back(glm::vec3(x, 50, 0));

			auto rotation_x = glm::rotate(glm::mat4(), (ofGetFrameNum() * span + x * span + 300) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			for (auto& vertex : vertices) {

				vertex = glm::vec3(x, y, 0) + glm::vec4(vertex, 0) * rotation_x;
			}

			this->mesh.addVertices(vertices);

			this->mesh.addIndex(this->mesh.getNumVertices() - 1);
			this->mesh.addIndex(this->mesh.getNumVertices() - 2);

			if (x > -150) {

				this->mesh.addIndex(this->mesh.getNumVertices() - 1);
				this->mesh.addIndex(this->mesh.getNumVertices() - 3);

				this->mesh.addIndex(this->mesh.getNumVertices() - 2);
				this->mesh.addIndex(this->mesh.getNumVertices() - 4);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	this->mesh.drawWireframe();

	for (auto& vertex : this->mesh.getVertices()) {

		ofDrawSphere(vertex, 3);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}