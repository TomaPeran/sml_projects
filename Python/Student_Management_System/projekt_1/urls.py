"""
URL configuration for projekt_1 project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from app import views

urlpatterns = [
    path('admin/', admin.site.urls),
    ##############

    
    path('login/', views.login, name='login'),
    path('logout/', views.logout_view, name='logout'),


    path('list_Professors/', views.list_Professors, name='list_Professors'),
    path('list_Students/', views.list_Students, name='list_Students'),
    path('list_Subjects/', views.list_Subjects, name='list_Subjects'),

    path('delete_User/<int:id>/', views.delete_User, name="delete_User"),
    path('confirm_User/<int:id>/', views.confirm_User, name="confirm_User"),
    path('edit_User/<int:id>/', views.edit_User, name="edit_User"),

    path('list_Students/add_Student/', views.add_Student, name='add_Student'),
    path('list_Professors/add_Professor/', views.add_Professor, name='add_Professor'),


    path('list_Subjects/add_Subject/', views.add_Subject, name='add_Subject'),
    path('list_Subjects/delete_Subject/<int:id>/', views.delete_Subject, name="delete_Subject"),
    path('confirm_Subject/<int:id>/', views.confirm_Subject, name="confirm_Subject"),
    path('list_Subjects/edit_Subject/<int:id>/', views.edit_Subject, name="edit_Subject"),

    path('list_Professors/prof_Subjects/<int:id>/', views.prof_Subjects, name="prof_Subjects"),
    path('subject_Students/<int:id>/<int:prof_id>/', views.subject_Students, name="subject_Students"),


    path('insertion/<int:student>/', views.enrollment_Insertion, name="enrollment_Insertion"),
    path('all_Enrollments/', views.all_Enrollments, name="all_Enrollments"),
    path('edit_Enrollments/<int:id>/', views.edit_Enrollments, name="edit_Enrollments"),
    path('student_Enrollment/<int:id>/', views.student_Enrollment, name="student_Enrollment"),
    path('delete_Enrollment/<int:id>/<int:student>/', views.delete_Enrollment, name="delete_Enrollment"),
    path('confirm_Enrollment/<int:id>/<int:student>/', views.confirm_Enrollment, name="confirm_Enrollment"),
    path('add_to_Subjects/<int:subject>/<int:student>/', views.add_to_Subjects, name="add_to_Subjects"),

    path('prof_Edits_Student/<int:subject>/<int:student>/<int:prof>/', views.prof_Edits_Student, name="prof_Edits_Student"),

    path('enrolled_Subjects/<int:id>/', views.enrolled_Subjects, name="enrolled_Subjects"),
    path('all_Students_Subjects/<int:id>/', views.all_Students_Subjects, name="all_Students_Subjects"),

    path('student_Details/<int:student>/<int:prof>/<int:subject>/', views.student_Details, name="student_Details"),

    path('list_Students/tmp_1/', views.tmp_1, name="tmp_1"),
    path('list_Students/tmp_2/<int:id>', views.tmp, name="tmp"),



]
