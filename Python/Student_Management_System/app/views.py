from django.shortcuts import render, redirect
from django.http import HttpResponse, HttpResponseNotAllowed
from .forms import RoleForm, myUserForm, LoginForm, SubjectsForm, EnrollmentForm_Form
from .models import Role, myUser, Subjects, EnrollmentForm
from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, logout as auth_logout , login as auth_login
from django.contrib.auth.decorators import user_passes_test


# Create your views here.
##################################

def login(request):
    if request.method == 'GET':
        form = LoginForm()
        return render(request, 'login.html', {"data":None, "form":form})
    
    elif request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            email = form.cleaned_data.get('email')
            password = form.cleaned_data.get('password')
            user = authenticate(request, email=email, password=password)
            if user:
                auth = auth_login(request, user)
            else:
                form = LoginForm()
                return render(request, 'login.html', {"data":True, "form":form})
            if user.role_id == 3: ## admin
                return render(request, 'list_Subjects.html', {"data": Subjects.objects.all()})
            ##########################################
            elif user.role_id == 4: ## prof
                id = vars(user)["id"]
                return render(request, 'professors_Subjects.html', {"data" : Subjects.objects.filter(professor = id), "prof" : id})
            ##########################################
            elif user.role_id == 5: ## student
                id = vars(user)["id"]
                return enrolled_Subjects(request, id)
            ##########################################
        form = LoginForm()
        return render(request, 'login.html', {"data":True, "form":form})        
    else:
        return HttpResponseNotAllowed(['GET', 'POST']) ## custom error dignit

def logout_view(request):
    auth_logout(request)
    return redirect('login')

##############----ADMIN----###################

def admin_Check(user):
    return user.role_id == 3 ## admin

def professor_Check(user):
    return user.role_id == 4 ## professor

def student_Check(user):
    return user.role_id == 5 ## student

def admin_or_professor_Check(user):
    return admin_Check(user) or professor_Check(user)


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/") 
def list_Subjects(request):
    return render(request, 'list_Subjects.html', {"data" : Subjects.objects.all()})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def delete_Subject(request, id): ##
    subject = Subjects.objects.get(id=id)
    if "Yes" in request.POST:
        subject.delete()
    
    return render(request, 'list_Subjects.html', {"data": Subjects.objects.all()})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def confirm_Subject(request, id):
    if request.method == 'GET':
        return render(request, 'delete_Subject.html', {"data":id})
    else:
        return HttpResponseNotAllowed()


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def add_Subject(request):
    if request.method == 'GET':
        return render(request, 'add_Subject.html',{"form": SubjectsForm()})
    
    elif request.method == 'POST':
        subject = SubjectsForm(request.POST)
        if subject.is_valid():
            subject.save()
            subject = SubjectsForm()
            return render(request, 'add_Subject.html', {"form": subject})
    
    else:
        return HttpResponseNotAllowed()    


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def edit_Subject(request, id):
    subject = Subjects.objects.get(id=id)
    if request.method == 'GET':
        form = SubjectsForm(instance=subject)
        return render(request, 'edit_Subject.html',{"form": form})

    elif request.method == 'POST':
        form = SubjectsForm(request.POST, instance=subject)
        if form.is_valid():
            form.save()
            return render(request, 'list_Subjects.html', {"data": Subjects.objects.all()})
    
    else:
        return HttpResponseNotAllowed() 


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def list_Professors(request):
    return render(request, 'list_Professors.html', {"data" : myUser.objects.filter(role_id = 4)})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def list_Students(request):
    return render(request, 'list_Students.html', {"data" : myUser.objects.filter(role_id = 5)})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def delete_User(request, id): ##
    user = myUser.objects.get(id=id)
    if "Yes" in request.POST:
        user.delete()
    
    role_id = vars(user)['role_id']
    if role_id == 4:
        return render(request, 'list_Professors.html', {"data": myUser.objects.filter(role_id=4)})
    elif role_id == 5:
        return render(request, 'list_Students.html', {"data": myUser.objects.filter(role_id=5)})
    else:
        return HttpResponseNotAllowed()


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def confirm_User(request, id):
    if request.method == 'GET':
        return render(request, 'delete_User.html', {"data":id})
    else:
        return HttpResponseNotAllowed()


@login_required(login_url="/login/")
@user_passes_test(admin_or_professor_Check, login_url="/login/")
def edit_User(request, id):
    user = myUser.objects.get(id=id)
    role = vars(user)['role_id']  
    if request.method == 'GET':
        if user is not None:
            return render(request, 'edit_User.html',{"form": myUserForm(instance=user), "state":role})
    
    elif request.method == 'POST':
        form = myUserForm(request.POST, instance=user)
        if form.is_valid():
            form.save()
            if role == 4:
                return render(request, 'list_Professors.html', {"data": myUser.objects.filter(role_id=4)}) ## odluci se jeli bolje ovo ili da vraca na nes drugo, mora biti GET kod ispisa
            elif role == 5:
                return render(request, 'list_Students.html', {"data": myUser.objects.filter(role_id=5)}) ## odluci se jeli bolje ovo ili da vraca na nes drugo, mora biti GET kod ispisa

    return HttpResponseNotAllowed(['GET', 'POST']) 


###################################################
@login_required(login_url="/login/")
def add_User_POST(request):
    form = myUserForm(request.POST)
    if form.is_valid():
        user = form.save(commit=False)
        user.set_password(form.cleaned_data['password'])  # Hash the password
        user.save()
        if vars(user)['role_id'] == 4: ## prof
            return render(request, 'list_Professors.html', {"data": myUser.objects.filter(role_id=4)})
        elif vars(user)['role_id'] == 5: ## student
            return render(request, 'list_Students.html', {"data": myUser.objects.filter(role_id=5)})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def add_Student(request):
    if request.method == 'GET':
        return render(request, 'add_User.html',{"form": myUserForm(), "state":5})
    elif request.method == 'POST':
        if "None" not in request.POST['status'] and not (myUser.objects.filter(email=request.POST['email'])):
            return add_User_POST(request)
        else:
            return render(request, 'add_User.html',{"form": myUserForm(), "state":5, "flag":True})
    else:
        return HttpResponseNotAllowed()


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def add_Professor(request):
    if request.method == 'GET':
        return render(request, 'add_User.html',{"form": myUserForm(), "state":4})
    elif request.method == 'POST':
        if "None" in request.POST['status'] and not (myUser.objects.filter(email=request.POST['email'])):
            return add_User_POST(request)
        else:
            return render(request, 'add_User.html',{"form": myUserForm(), "state":4, "flag":True})
    else:
        return HttpResponseNotAllowed()


###################################################
## samo admin i profesor, postavi i za ostale funkcije
@login_required(login_url="/login/")
@user_passes_test(admin_or_professor_Check, login_url="/login/")
def prof_Subjects(request, id):
    if request.user.role_id == 3:
        return render(request, 'professors_Subjects.html', {"data": Subjects.objects.filter(professor = id), "prof" : 0})
    else:
        return render(request, 'professors_Subjects.html', {"data": Subjects.objects.filter(professor = id), "prof" : id})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def all_Enrollments(request):
    return render(request, 'all_Enrollments.html', {"data" : EnrollmentForm.objects.all()})


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def enrollment_Insertion(request, student):
    enr = EnrollmentForm(student_id_id=student)
    if request.method == 'GET':
        return render(request, 'enrollment.html', {"form" : EnrollmentForm_Form(instance=enr), "data" : False})
        ###########################   
    elif request.method == 'POST':
        form = EnrollmentForm_Form(request.POST)
        if form.is_valid():
            form.save()
            return render(request, 'all_Enrollments.html', {"data" : EnrollmentForm.objects.all()})        
        else:
            return render(request, 'enrollment.html', {"form" : EnrollmentForm_Form(), "data" : True})        
        ###########################
    else:
        return HttpResponseNotAllowed(['GET', 'POST'])


@login_required(login_url="/login/")
@user_passes_test(admin_Check, login_url="/login/")
def edit_Enrollments(request, id):
    enroll = EnrollmentForm.objects.get(id=id)
    if request.method == 'GET' and enroll is not None:
        return render(request, 'enrollment.html', {"form": EnrollmentForm_Form(instance=enroll)})

    elif request.method == 'POST':
        form = EnrollmentForm_Form(request.POST, instance=enroll)
        if form.is_valid():
            form.save()
            return render(request, 'all_Enrollments.html', {"data": EnrollmentForm.objects.all()})
    
    return HttpResponseNotAllowed()


################-----------PROFESSOR-----##########################

@login_required(login_url="/login/")
@user_passes_test(admin_or_professor_Check, login_url="/login/")
def subject_Students(request, id, prof_id):
    enr_forms = EnrollmentForm.objects.filter(subject_id=id)
    return render(request, 'subject_Students.html', {"data" : enr_forms, "prof" : prof_id, "subject" : id})


@login_required(login_url="/login/")
@user_passes_test(admin_or_professor_Check, login_url="/login/")
def student_Enrollment(request, id):
    student_enr = EnrollmentForm.objects.filter(student_id = id)
    student = myUser.objects.get(id=id)
    return render(request, 'student_Enrollment.html', {"data" : student_enr, "student" : student})


@login_required(login_url="/login/")
@user_passes_test(admin_or_professor_Check, login_url="/login/")
def prof_Edits_Student(request, subject, student, prof):
    enroll = EnrollmentForm.objects.get(student_id_id=student, subject_id_id=subject)
    if request.method == 'GET':
        enr_form = EnrollmentForm_Form(instance=enroll)
        return render(request, 'prof_Edits_Student.html', {"form" : enr_form, "prof" : prof, "subject" : subject})

    elif request.method == 'POST':
        form = EnrollmentForm_Form(request.POST, instance=enroll)
        if form.is_valid():
            form.save()
            enr_forms = EnrollmentForm.objects.filter(subject_id_id=subject)
            return render(request, 'subject_Students.html', {"data" : enr_forms, "prof" : prof, "subject" : subject})
    
    return HttpResponseNotAllowed(['GET', 'POST'])


@login_required(login_url="/login/")
def confirm_Enrollment(request, id, student):
    if request.method == 'GET':
        return render(request, 'delete_Enrollment.html', {"id":id, "student":student})
    else:
        return HttpResponseNotAllowed()


@login_required(login_url="/login/")
def delete_Enrollment(request, id, student): ##
    enroll = EnrollmentForm.objects.get(id=id)
    if "Yes" in request.POST:
        enroll.delete()

    if request.user.role_id == 3:
        return student_Enrollment(request, student)
    else:
        return enrolled_Subjects(request, student)


######################---STUDENT---######################

@login_required(login_url="/login/")
@user_passes_test(student_Check, login_url="/login/")
def enrolled_Subjects(request, id):
    enrollments = EnrollmentForm.objects.filter(student_id_id = id)
    array = [Subjects.objects.get(id=enrollment.subject_id_id) for enrollment in enrollments]
    return render(request, 'enrolled_Subjects.html', {"data" : array, "student" : id, "enroll":enrollments})


@login_required(login_url="/login/")
@user_passes_test(student_Check, login_url="/login/")
def all_Students_Subjects(request, id):
    all_subjects = Subjects.objects.all()
    enrollments = EnrollmentForm.objects.filter(student_id_id = id)

    array = [Subjects.objects.get(id=enrollment.subject_id_id) for enrollment in enrollments]
    new_array = [subject for subject in all_subjects if subject not in array]

    return render(request, 'all_Students_Subjects.html', {"data" : new_array, "student" : id})


@login_required(login_url="/login/")
@user_passes_test(student_Check, login_url="/login/")
def add_to_Subjects(request, subject, student):
    enroll = EnrollmentForm(
        subject_id_id = subject,
        student_id_id = student,
        status = "Upisan"
        )
    
    enroll.save()
    return all_Students_Subjects(request, student)


@login_required(login_url="/login/")
@user_passes_test(admin_or_professor_Check, login_url="/login/")
def student_Details(request, student, prof, subject):
    details = myUser.objects.get(id=student)
    return render(request, 'student_Details.html', {"details" : details, "prof" : prof, "subject":subject})



# def confirm_deletion(request, id, string):
#     if request.method == 'GET':
#         return render(request, 'confirm_deletion.html', {"id" : id, "string":string})
#     else:
#         return HttpResponseNotAllowed(['GET', 'POST'])


def tmp_1(request):
    all_enr = EnrollmentForm.objects.all()
    lista = list()
    for enr in all_enr:
        if enr.status != 'Neupisan': 
            subject = Subjects.objects.get(name = enr.subject_id)

            if enr.student_id.first_name not in lista:
                lista.append(enr.student_id.first_name)
                lista.append(subject.ects)
            else:
                lista[lista.index(enr.student_id.first_name) + 1] += subject.ects

    # data = [ lista[i - 1] for i in range(0, len(lista)) if lista[i] > 29]
    return render(request, 'tmp_1.html', {'lista': lista})


def tmp(request, id):
    all_subjects = Subjects.objects.all()
    enrollments = EnrollmentForm.objects.filter(student_id_id = id)

    array = [Subjects.objects.get(id=enrollment.subject_id_id) for enrollment in enrollments]

    provjera = [enroll.status == 'Polozen' for enroll in enrollments if enroll.subject_id.semester == 2 or enroll.subject_id.semester == 1]

    if False in provjera:
        new_array = [subject for subject in all_subjects if subject not in array]
    else:
        new_array = [subject for subject in all_subjects if subject not in array]
    
    data = new_array
    return render(request, 'tmp_2.html', {'data': data})
