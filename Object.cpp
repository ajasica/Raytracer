//////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////


#include "common.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Sphere::intersect(vec4 p0_w, vec4 V_w){
											//in slides as ray start and ray direction
  IntersectionValues result;
  //TODO: Ray-sphere setup

  //This will change
  vec4 p0_o = INVC * p0_w;
  vec4 V_o = normalize(INVCStar * V_w);

  result.t_o = raySphereIntersection(p0_o, V_o);
  result.t_w = result.t_o / length(INVCStar * V_w);

  result.P_w = p0_w + result.t_w * V_w;
  result.P_o = p0_o + result.t_o * V_o;

  result.N_o = normalize(result.P_o - vec4(0.0,0.0, 0.0, 1.0));

  result.N_w = TRANINVC * result.N_o;  
  result.N_w.w = 0.0;	//zero out w component
  result.N_w = normalize(result.N_w);

  return result;
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin O and radius r    : Find t ------- */
double Sphere::raySphereIntersection(vec4 p0, vec4 V, vec4 O, double r){
  double t  = std::numeric_limits< double >::infinity();

  //what is this doing?
  double a = 1.0;
  double b = dot(2.0*V, p0 - O);
  double c = length(p0 - O) * length(p0 - O) - r*r;
  double in_sqrt = b * b - 4.0*a*c;

  if (in_sqrt < 0.0) {
	//ray doesn't hit sphere
	  return std::numeric_limits<double>::infinity();
  }

  double t_plus = (-b + sqrt(in_sqrt)) / 2 * a;
  double t_minus = (-b - sqrt(in_sqrt)) / 2 * a;

  if (t_plus < EPSILON) { t_plus = std::numeric_limits<double>::infinity(); }	//EPSILON 1e-3
  if (t_minus < EPSILON) { t_minus = std::numeric_limits<double>::infinity(); }



  //TODO: Ray-sphere intersection;
  return fmin(t_plus, t_minus);
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0_w, vec4 V_w){
  IntersectionValues result;

  //This will change
  vec4 p0_o = INVC * p0_w;
  vec4 V_o = normalize(INVCStar * V_w);

  result.t_o = raySquareIntersection(p0_o, V_o);
  result.t_w = result.t_o / length(INVCStar * V_w);

  result.P_w = p0_w + result.t_w * V_w;
  result.P_o = p0_o + result.t_o * V_o;

  result.N_o = vec4(0.0, 0.0, 1.0, 0.0);
  result.N_w = TRANINVC * result.N_o;
  result.N_w *= vec4(1.0, 1.0, 1.0, 0.0);	//zero out w component of vec4
  result.N_w = normalize(result.N_w);

  return result;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V){
  double t   = std::numeric_limits< double >::infinity();
  //TODO: Ray-square intersection;
   
  vec4 N = vec4(0.0, 0.0, 1.0, 0.0);		//vector
  vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);	//point
  
  double a = dot(N, origin - p0);
  double b = dot(N, V);
  if (b == 0.0) { return std::numeric_limits<double>::infinity(); }
  t = a / b;

  if (t < EPSILON) { return std::numeric_limits<double>::infinity(); }

  vec4 point = p0 + t * V;

  //confirm point within the unit square
  if (point.x > 1 || point.x < -1) { return std::numeric_limits<double>::infinity(); }
  if (point.y > 1 || point.y < -1) { return std::numeric_limits<double>::infinity(); }
  else { return t; }


}
