from django import forms
from app.models import myUser, Subjects, EnrollmentForm, Role


class myUserForm(forms.ModelForm):
    class Meta:
        model = myUser
        fields = ["first_name", "last_name", "email", "password", "status", "role"]
        widgets = {
            'first_name': forms.TextInput(attrs={'class': 'user_input'}),
            'last_name': forms.TextInput(attrs={'class': 'user_input'}),
            'email': forms.EmailInput(attrs={'class': 'user_input'}),
            'password': forms.PasswordInput(attrs={'class': 'user_input'}),
            'status' : forms.Select(choices=myUser.STATUS_CHOICES, attrs={'class':'user_input'}),
            'role' : forms.Select(attrs={'class':'user_input'}),
        }

    def __init__(self, *args, **kwargs):
        super(myUserForm, self).__init__(*args, **kwargs)
        self.fields['password'].widget = forms.PasswordInput(attrs={'class': 'user_input'})
        self.fields['role'].queryset = Role.objects.all() 



class SubjectsForm(forms.ModelForm):
    class Meta:
        model = Subjects
        fields = ["name", "code", "ects", "semester", "elective", "professor"]
        widgets = {
            'name': forms.TextInput(attrs={'class': 'user_input'}),
            'code': forms.TextInput(attrs={'class': 'user_input'}),
            'ects': forms.TextInput(attrs={'class': 'user_input'}),
            'semester': forms.TextInput(attrs={'class': 'user_input'}),
            'elective' : forms.Select(choices=myUser.STATUS_CHOICES, attrs={'class':'user_input'}),
            'professor' : forms.Select(attrs={'class':'user_input'}),
        }
    def __init__(self, *args, **kwargs):
        super(SubjectsForm, self).__init__(*args, **kwargs)
        self.fields['professor'].queryset = myUser.objects.filter(role_id=4) ## query odreduje polje professor da prikaze samo profe 



class EnrollmentForm_Form(forms.ModelForm):
    class Meta:
        model = EnrollmentForm
        fields = '__all__'
        widgets = {
            'status' : forms.Select(attrs={'class':'user_input'}),
        }
        
        ## \~/ 
    def __init__(self, *args, **kwargs):
        user = kwargs.pop('user', None)
        super(EnrollmentForm_Form, self).__init__(*args, **kwargs)
        self.fields['student_id'] =  forms.ModelChoiceField(
            queryset=myUser.objects.filter(role_id=5),
            widget=forms.Select(attrs={'class': 'user_input'}),
        )
        self.fields['subject_id'] = forms.ModelChoiceField(
            queryset=Subjects.objects.all(),
            widget=forms.Select(attrs={'class': 'user_input'}),
            empty_label="Select Subject"
        )

        # ne radi user.is_superuser, pogledaj
        # self.fields['student_id'].disabled = True
        # self.fields['subject_id'].disabled = True


class RoleForm(forms.ModelForm):
    class Meta:
        model = Role
        fields = '__all__'




class LoginForm(forms.Form):
    email = forms.EmailField(widget=forms.EmailInput(attrs={'class':'login_input'}), label='Email address', max_length=255)
    password = forms.CharField(widget=forms.PasswordInput(attrs={'class':'login_input'}), label='Password')
