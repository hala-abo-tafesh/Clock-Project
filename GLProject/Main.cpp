// GLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Polygon.cpp"
#include "Sphere.h"
#include <ctime> 

using namespace glm;

int width = 800;
int height = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 4.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.002f; 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cross(cameraFront,normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, 1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, -1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
}


Polygon makeTick(float width, float height, glm::vec3 color)
{
	std::vector<glm::vec3> v = {
		glm::vec3(-width / 2, 0.0f, 0.01f),
		glm::vec3(width / 2, 0.0f, 0.01f),
		glm::vec3(width / 2, height, 0.01f),
		glm::vec3(-width / 2, height, 0.01f)
	};

	return Polygon(v, color);
}


int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Lecture 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");

	std::vector<vec3> vertices0 = {}; //front face
	vertices0.push_back(vec3(0.7f, 0.7f, 0.0f)); //f up right
	vertices0.push_back(vec3(-0.7f, 0.7f, 0.0f)); //f up left
	vertices0.push_back(vec3(-0.7f, -0.7f, 0.0f)); //f buttom left
	vertices0.push_back(vec3(0.7f, -0.7f, 0.0f)); // f buttom rihgt

	Polygon axis = Polygon(vertices0, vec3(0.35f, 0.0f, 0.35f));

	std::vector<vec3> vertices1 = {}; //back face
	vertices1.push_back(vec3(0.7f, 0.7f, -0.4f));  //b up right
	vertices1.push_back(vec3(-0.7f, 0.7f, -0.4f));  //b up left
	vertices1.push_back(vec3(-0.7f, -0.7f, -0.4f)); //b buttom left
	vertices1.push_back(vec3(0.7f, -0.7f, -0.4f)); // b buttom rihgt
	
	Polygon Polygon1 = Polygon(vertices1, vec3(0.35f, 0.0f, 0.35f));

	std::vector<vec3> vertices2 = {};  //left side
	vertices2.push_back(vec3(-0.7f, 0.7f, -0.4f)); //b up left
	vertices2.push_back(vec3(-0.7f, 0.7f, 0.0f)); //f up left
	vertices2.push_back(vec3(-0.7f, -0.7f, 0.0f)); //f buttom left
	vertices2.push_back(vec3(-0.7f, -0.7f, -0.4f)); //b buttom left
	Polygon Polygon2 = Polygon(vertices2, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices3 = {}; //right side
	vertices3.push_back(vec3(0.7f, 0.7f, -0.4f));  //b up right;
	vertices3.push_back(vec3(0.7f, 0.7f, 0.0f)); //f up right
	vertices3.push_back(vec3(0.7f, -0.7f, 0.0f)); // f buttom rihgt
	vertices3.push_back(vec3(0.7f, -0.7f, -0.4f)); // b buttom rihgt
	Polygon Polygon3 = Polygon(vertices3, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices4 = {}; //up
	vertices4.push_back(vec3(0.7f, 0.7f, -0.4f));  //b up right
	vertices4.push_back(vec3(-0.7f, 0.7f, -0.4f));  //b up left
	vertices4.push_back(vec3 (- 0.7f, 0.7f, 0.0f)); //f up left
	vertices4.push_back(vec3 (0.7f, 0.7f, 0.0f)); //f up right
	Polygon Polygon4 = Polygon(vertices4, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices5 = {}; //buttom
	vertices5.push_back(vec3(0.7f, -0.7f, -0.4f)); // b buttom rihgt
	vertices5.push_back(vec3(-0.7f, -0.7f, -0.4f)); //b buttom left
	vertices5.push_back(vec3(-0.7f, -0.7f, 0.0f)); //f buttom left
	vertices5.push_back(vec3(0.7f, -0.7f, 0.0f)); // f buttom rihgt
	Polygon Polygon5 = Polygon(vertices5, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices6 = {}; 
	vertices6.push_back(vec3(0.1f, -0.7f, -0.22f)); // b up rihgt
	vertices6.push_back(vec3(-0.1f, -0.7f, -0.22f)); //b up left
	vertices6.push_back(vec3(-0.1f, -1.5f, -0.22f)); //b buttom left
	vertices6.push_back(vec3(0.1f, -1.5f, -0.22f)); // b buttom rihgt
	Polygon Polygon6 = Polygon(vertices6, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices7 = {}; 
	vertices7.push_back(vec3(0.1f, -0.7f, -0.18f)); // f up rihgt
	vertices7.push_back(vec3(-0.1f, -0.7f, -0.18f)); //f up left
	vertices7.push_back(vec3(-0.1f, -1.5f, -0.18f)); //f buttom left
	vertices7.push_back(vec3(0.1f, -1.5f, -0.18f)); // f buttom rihgt
	Polygon Polygon7 = Polygon(vertices7, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices8 = {}; 
	vertices8.push_back(vec3(0.1f, -0.7f, -0.22f)); // b up rihgt
	vertices8.push_back(vec3(-0.1f, -0.7f, -0.22f)); //b up left
	vertices8.push_back(vec3(-0.1f, -0.7f, -0.18f)); //f up left
	vertices8.push_back(vec3(0.1f, -0.7f, -0.22f)); // b up rihgt
	Polygon Polygon8 = Polygon(vertices8, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices9 = {}; 
	vertices9.push_back(vec3(0.1f, -1.5f, -0.22f)); // b buttom rihgt
	vertices9.push_back(vec3(-0.1f, -1.5f, -0.22f)); //b buttom left
	vertices9.push_back(vec3(-0.1f, -1.5f, -0.18f)); //f buttom left
	vertices9.push_back(vec3(0.1f, -1.5f, -0.22f)); // b buttom rihgt
	Polygon Polygon9 = Polygon(vertices9, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices10 = {}; 
	vertices10.push_back(vec3(0.1f, -0.7f, -0.22f)); // b up rihgt
	vertices10.push_back(vec3(0.1f, -0.7f, -0.18f)); // f up rihgt
	vertices10.push_back(vec3(0.1f, -1.5f, -0.18f)); // f buttom rihgt
	vertices10.push_back(vec3(0.1f, -1.5f, -0.22f)); // b buttom rihgt
	Polygon Polygon10 = Polygon(vertices10, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> vertices11 = {}; 
	vertices11.push_back(vec3(-0.1f, -0.7f, -0.22f)); //b up left
	vertices11.push_back(vec3(-0.1f, -0.7f, -0.18f)); //f up left
	vertices11.push_back(vec3(-0.1f, -1.5f, -0.18f)); //f buttom left
	vertices11.push_back(vec3(-0.1f, -1.5f, -0.22f)); //b buttom left
	Polygon Polygon11 = Polygon(vertices11, vec3(0.933f, 0.51f, 0.933f));


	std::vector<vec3> bafaceclock = {}; 
	bafaceclock.push_back(vec3(0.5f, 0.5f, 0.0f)); // back up rihgt
	bafaceclock.push_back(vec3(-0.5f, 0.5f, 0.0f)); //b up left
	bafaceclock.push_back(vec3(-0.5f, -0.5f, 0.0f)); //b buttom left
	bafaceclock.push_back(vec3(0.5f, -0.5f, 0.0f)); // b buttom rihgt
	Polygon bafaceclockver = Polygon(bafaceclock, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> frfaceclock = {};  
	frfaceclock.push_back(vec3(0.5f, 0.5f, 0.1f)); // front up rihgt
	frfaceclock.push_back(vec3(-0.5f, 0.5f, 0.1f)); //f up left
	frfaceclock.push_back(vec3(-0.5f, -0.5f, 0.1f)); //f buttom left
	frfaceclock.push_back(vec3(0.5f, -0.5f, 0.1f)); // f buttom rihgt
	Polygon frfaceclockver = Polygon(frfaceclock, vec3(0.933f, 0.51f, 0.933f));


	std::vector<vec3> rifaceclock = {};  
	rifaceclock.push_back(vec3(0.5f, 0.5f, 0.0f)); // b up rihgt
	rifaceclock.push_back(vec3(0.5f, 0.5f, 0.1f)); // front up rihgt
	rifaceclock.push_back(vec3(0.5f, -0.5f, 0.1f)); // f buttom rihgt
	rifaceclock.push_back(vec3(0.5f, -0.5f, 0.0f)); // b buttom rihgt
	Polygon rifaceclockver = Polygon(rifaceclock, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> lefaceclock = {};  
	lefaceclock.push_back(vec3(-0.5f, 0.5f, 0.0f)); //b up left
	lefaceclock.push_back(vec3(-0.5f, 0.5f, 0.1f)); //f up left
	lefaceclock.push_back(vec3(-0.5f, -0.5f, 0.1f)); //f buttom left
	lefaceclock.push_back(vec3(-0.5f, -0.5f, 0.0f)); //b buttom left
	Polygon lefaceclockver = Polygon(lefaceclock, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> upfaceclock = {};  
	upfaceclock.push_back(vec3(0.5f, 0.5f, 0.0f)); // b up rihgt
	upfaceclock.push_back(vec3(-0.5f, 0.5f, 0.0f)); //b up left
	upfaceclock.push_back(vec3(-0.5f, 0.5f, 0.1f)); //f up left
	upfaceclock.push_back(vec3(0.5f, 0.5f, 0.1f)); // front up rihgt
	Polygon upfaceclockver = Polygon(upfaceclock, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> butfaceclock = {};  
	butfaceclock.push_back(vec3(0.5f, -0.5f, 0.0f)); // b buttom rihgt
	butfaceclock.push_back(vec3(-0.5f, -0.5f, 0.0f)); //b buttom left
	butfaceclock.push_back(vec3(-0.5f, -0.5f, 0.1f)); //f buttom left
	butfaceclock.push_back(vec3(0.5f, -0.5f, 0.1f)); // f buttom rihgt
	Polygon butfaceclockver = Polygon(butfaceclock, vec3(0.933f, 0.51f, 0.933f));

	std::vector<vec3> mark = {
	vec3(-0.01f, 0.0f, 0.11f),
	vec3(0.01f, 0.0f, 0.11f),
	vec3(0.01f, 0.08f, 0.11f),
	vec3(-0.01f, 0.08f, 0.11f)
	};
	Polygon hourMark(mark, vec3(0.0f, 0.0f, 0.0f));

	std::vector<vec3> hourHand = {
	vec3(-0.02f, 0.0f, 0.12f),   
	vec3(0.02f, 0.0f, 0.12f),   
	vec3(0.02f, 0.15f, 0.12f),  
	vec3(-0.02f, 0.15f, 0.12f)   
	};
	Polygon hourHandver(hourHand, vec3(0.3f, 0.0f, 0.3f));

	std::vector<vec3> minuteHand = {
	vec3(-0.015f, 0.0f, 0.12f),
	vec3(0.015f, 0.0f, 0.12f),
	vec3(0.015f, 0.25f, 0.12f),
	vec3(-0.015f, 0.25f, 0.12f)
	}; 
	Polygon minuteHandver(minuteHand, vec3(0.0f, 0.0f, 0.0f));

	std::vector<vec3> secondHand = {
	vec3(-0.008f, 0.0f, 0.12f),   
	vec3(0.008f, 0.0f, 0.12f),   
	vec3(0.008f, 0.28f, 0.12f),  
	vec3(-0.008f, 0.28f, 0.12f)  
	};
	Polygon secondHandver(secondHand, vec3(1.0f, 1.0f, 1.0f));


	Sphere ball(0.2f, 36, 18, glm::vec3(0.3f, 0.0f, 0.3f));

	ourShader.use();

	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	//projection = ortho(-(float)width, (float)width, -(float)height, (float)height, 0.01f, 100.0f);;
	ourShader.setMat4("projection", projection);

	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = mat4(1.0f);
		view = translate(view, vec3(0.0f, 0.0f, -4.0f));
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);

		mat4 transformation = mat4(1.0f);

		axis.transformation(transformation);
		axis.draw(ourShader);
		
		Polygon1.transformation(transformation);
		Polygon1.draw(ourShader);

		Polygon2.transformation(transformation);
		Polygon2.draw(ourShader);

		Polygon3.transformation(transformation);
		Polygon3.draw(ourShader);

		Polygon4.transformation(transformation);
		Polygon4.draw(ourShader);

		Polygon5.transformation(transformation);
		Polygon5.draw(ourShader);

		bafaceclockver.transformation(transformation);
		bafaceclockver.draw(ourShader);

		frfaceclockver.transformation(transformation);
		frfaceclockver.draw(ourShader);

		rifaceclockver.transformation(transformation);
		rifaceclockver.draw(ourShader);

		lefaceclockver.transformation(transformation);
		lefaceclockver.draw(ourShader);

		upfaceclockver.transformation(transformation);
		upfaceclockver.draw(ourShader);

		butfaceclockver.transformation(transformation);
		butfaceclockver.draw(ourShader);

		for (int i = 0; i < 12; i++)
		{
			float angle = glm::radians(i * 30.0f); // ?? 30 ???? ???

			glm::mat4 T = glm::mat4(1.0f);


			T = glm::rotate(T, angle, glm::vec3(0, 0, 1));

			
			T = glm::translate(T, glm::vec3(0.0f, 0.42f, 0.0f));

			
			hourMark.transformation(T);
			hourMark.draw(ourShader);
		}

		
		std::time_t now = std::time(nullptr);
		std::tm lt;
		localtime_s(&lt, &now);

		int hours = lt.tm_hour;   // 0..23
		int minutes = lt.tm_min;    // 0..59
		int seconds = lt.tm_sec;    // 0..59

		
		float hourAngle = glm::radians((hours % 12) * 30.0f + minutes * 0.5f + seconds * (0.5f / 60.0f));
		float minuteAngle = glm::radians(minutes * 6.0f + seconds * 0.1f);
		float secondAngle = glm::radians(seconds * 6.0f);

		float angle = sin(hourAngle + minuteAngle + secondAngle) * glm::radians(25.0f);

		glm::mat4 pendulum = glm::mat4(1.0f);
		pendulum = glm::translate(pendulum, glm::vec3(0.0f, -0.7f, -0.2f));
		pendulum = glm::rotate(pendulum,(float) sin(2*glfwGetTime()) / 4, glm::vec3(0.0f, 0.0f, 1.0f));
		pendulum = glm::translate(pendulum, glm::vec3(0.0f, 0.7f, 0.2f));

		std::vector<Polygon> pendulumParts = { Polygon6, Polygon7, Polygon8,Polygon9,Polygon10, Polygon11 };

		for (Polygon& p : pendulumParts) {
			p.transformation(pendulum* transformation);
			p.draw(ourShader);
		}


		
		glm::mat4 ballTrans = pendulum;
		ballTrans = glm::translate(ballTrans, glm::vec3(0.0f, -1.5f, -0.2f));
		ball.transformation(ballTrans);
		ball.draw(ourShader);

		
		glm::mat4 hT = glm::mat4(1.0f);
		hT = glm::translate(hT, glm::vec3(0.0f, 0.0f, 0.01f));
		hT = glm::rotate(hT, -hourAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		hourHandver.transformation(hT);
		hourHandver.draw(ourShader);

		
		glm::mat4 mT = glm::mat4(1.0f);
		mT = glm::translate(mT, glm::vec3(0.0f, 0.0f, 0.015f));
		mT = glm::rotate(mT, -minuteAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		minuteHandver.transformation(mT);
		minuteHandver.draw(ourShader);

		
		glm::mat4 sT = glm::mat4(1.0f);
		sT = glm::translate(sT, glm::vec3(0.0f, 0.0f, 0.02f));
		sT = glm::rotate(sT, -secondAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		secondHandver.transformation(sT);
		secondHandver.draw(ourShader);
		 

		bafaceclockver.transformation(transformation);
		bafaceclockver.draw(ourShader);

		frfaceclockver.transformation(transformation);
		frfaceclockver.draw(ourShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}